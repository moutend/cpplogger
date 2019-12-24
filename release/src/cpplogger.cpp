#include <chrono>
#include <cpplogger/cpplogger.h>
#include <cpprest/http_client.h>
#include <cstring>
#include <mutex>
#include <sstream>

#ifdef _UTF16_STRINGS
#define __key(x) L##x
#else
#define __key(x) x
#endif

using namespace web;
using namespace web::http;

namespace Logger {
Logger::Logger(const std::wstring &source, const std::wstring &version,
               int32_t maxMessages) {
  mSource = source;
  mVersion = version;
  mMaxMessages = maxMessages;
  mMessages = new LogMessage *[maxMessages] { nullptr };
}

Logger::~Logger() {
  Clear();

  delete[] mMessages;
  mMessages = nullptr;
}

void Logger::Info(const std::wstring &message, int64_t threadId,
                  const std::wstring &path) {
  Write(L"INFO", message, threadId, path);
}

void Logger::Warn(const std::wstring &message, int64_t threadId,
                  const std::wstring &path) {
  Write(L"WARN", message, threadId, path);
}

void Logger::Fail(const std::wstring &message, int64_t threadId,
                  const std::wstring &path) {
  Write(L"FAIL", message, threadId, path);
}

void Logger::Write(const std::wstring &level, const std::wstring &message,
                   int64_t threadId, const std::wstring &path) {
  std::lock_guard<std::mutex> guard(mMutex);

  int64_t now = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now().time_since_epoch())
                    .count();

  int64_t sec = now / 1000000000;
  int64_t nano = now % 1000000000;

  delete mMessages[mIndex];
  mMessages[mIndex] = nullptr;
  mMessages[mIndex] = new LogMessage();

  size_t levelLength = std::wcslen(level.c_str());
  mMessages[mIndex]->Level = new wchar_t[levelLength + 1]{};
  std::wmemcpy(mMessages[mIndex]->Level, level.c_str(), levelLength);

  size_t messageLength = std::wcslen(message.c_str());
  mMessages[mIndex]->Message = new wchar_t[messageLength + 1]{};
  std::wmemcpy(mMessages[mIndex]->Message, message.c_str(), messageLength);

  size_t pathLength = std::wcslen(path.c_str());
  mMessages[mIndex]->Path = new wchar_t[pathLength + 1]{};
  std::wmemcpy(mMessages[mIndex]->Path, path.c_str(), pathLength);

  mMessages[mIndex]->ThreadId = threadId;
  mMessages[mIndex]->UnixTimestampSec = sec;
  mMessages[mIndex]->UnixTimestampNano = nano;

  mIndex = (mIndex + 1) % mMaxMessages;
}

void Logger::Clear() {
  std::lock_guard<std::mutex> guard(mMutex);

  for (int32_t i = 0; i < mMaxMessages; i++) {
    delete mMessages[i];
    mMessages[i] = nullptr;
  }

  mIndex = 0;
}

json::value Logger::ToJSON() {
  json::value messages;

  for (int32_t i = 0; i < mMaxMessages; i++) {
    if (mMessages[i] == nullptr) {
      break;
    }

    json::value m;
    m[__key("level")] = json::value(mMessages[i]->Level);
    m[__key("source")] = json::value(mSource.c_str());
    m[__key("version")] = json::value(mVersion.c_str());
    m[__key("message")] = json::value(mMessages[i]->Message);
    m[__key("threadId")] = json::value(mMessages[i]->ThreadId);
    m[__key("unixTimestampSec")] = json::value(mMessages[i]->UnixTimestampSec);
    m[__key("unixTimestampNano")] =
        json::value(mMessages[i]->UnixTimestampNano);
    m[__key("path")] = json::value(mMessages[i]->Path);

    messages[i] = m;
  }

  json::value o;

  o[__key("messages")] = messages;

  return o;
}
} // namespace Logger
