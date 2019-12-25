#include <chrono>
#include <cpplogger/cpplogger.h>
#include <cstring>
#include <mutex>

using namespace web;

namespace Logger {
Logger::Logger(const utility::string_t &source,
               const utility::string_t &version, int32_t maxMessages) {
  mSource = source;
  mVersion = version;
  mMaxMessages = maxMessages;
  mMessages = new LogMessage[maxMessages]{};
}

Logger::~Logger() {
  Clear();

  delete[] mMessages;
}

void Logger::Info(const utility::string_t &message, int64_t threadId,
                  const utility::string_t &path) {
  Write(__ustring("INFO"), message, threadId, path);
}

void Logger::Warn(const utility::string_t &message, int64_t threadId,
                  const utility::string_t &path) {
  Write(__ustring("WARN"), message, threadId, path);
}

void Logger::Fail(const utility::string_t &message, int64_t threadId,
                  const utility::string_t &path) {
  Write(__ustring("FAIL"), message, threadId, path);
}

void Logger::Write(const utility::string_t &level,
                   const utility::string_t &message, int64_t threadId,
                   const utility::string_t &path) {
  std::lock_guard<std::mutex> guard(mMutex);

  int64_t now = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::system_clock::now().time_since_epoch())
                    .count();

  int64_t sec = now / 1000000000;
  int64_t nano = now % 1000000000;

  mMessages[mIndex].Level = level;
  mMessages[mIndex].Message = message;
  mMessages[mIndex].Path = path;
  mMessages[mIndex].ThreadId = threadId;
  mMessages[mIndex].UnixTimestampSec = sec;
  mMessages[mIndex].UnixTimestampNano = nano;

  mMessageCount += 1;
  mIndex = (mIndex + 1) % mMaxMessages;
}

void Logger::Clear() {
  for (int32_t i = 0; i < mMaxMessages; i++) {
    mMessages[i].Level.clear();
    mMessages[i].Message.clear();
    mMessages[i].Path.clear();
    mMessages[i].ThreadId = 0;
    mMessages[i].UnixTimestampSec = 0;
    mMessages[i].UnixTimestampNano = 0;
  }

  mMessageCount = 0;
  mIndex = 0;
}

json::value Logger::ToJSON() {
  json::value messages;

  for (int32_t i = 0; i < mMaxMessages; i++) {
    if (i > mMessageCount - 1) {
      break;
    }

    json::value m;

    m[__ustring("level")] = json::value(mMessages[i].Level);
    m[__ustring("source")] = json::value(mSource);
    m[__ustring("version")] = json::value(mVersion);
    m[__ustring("message")] = json::value(mMessages[i].Message);
    m[__ustring("threadId")] = json::value(mMessages[i].ThreadId);
    m[__ustring("unixTimestampSec")] =
        json::value(mMessages[i].UnixTimestampSec);
    m[__ustring("unixTimestampNano")] =
        json::value(mMessages[i].UnixTimestampNano);
    m[__ustring("path")] = json::value(mMessages[i].Path);

    messages[i] = m;
  }

  json::value o;

  o[__ustring("messages")] = messages;

  return o;
}

bool Logger::IsEmpty() { return mMessageCount == 0; }
void Logger::Lock() { mMutex.lock(); }
void Logger::Unlock() { mMutex.unlock(); }
} // namespace Logger
