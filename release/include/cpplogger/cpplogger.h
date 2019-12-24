#pragma once

#include <cpprest/http_client.h>
#include <cstdint>
#include <mutex>
#include <sstream>
#include <string>

#define WC_STRINGIFY2(x) L##x
#define WC_STRINGIFY1(x) WC_STRINGIFY2(x)
#define C_STRINGIFY2(x) #x
#define C_STRINGIFY1(x) C_STRINGIFY2(x)
#define __LONGFILE__                                                           \
  WC_STRINGIFY1(__FILE__) L":" WC_STRINGIFY1(C_STRINGIFY1(__LINE__))

using namespace web;
using namespace web::http;

namespace Logger {
class LogMessage {
public:
  LogMessage();
  ~LogMessage();

  wchar_t *Level = nullptr;
  wchar_t *Message = nullptr;
  wchar_t *Path = nullptr;
  int64_t ThreadId = 0;
  int64_t UnixTimestampSec = 0;
  int64_t UnixTimestampNano = 0;
};

class Logger {
public:
  Logger(const std::wstring &source, const std::wstring &version,
         int32_t maxMessages);
  ~Logger();

  void Info(const std::wstring &message, int64_t threadId,
            const std::wstring &fileName);
  void Warn(const std::wstring &message, int64_t threadId,
            const std::wstring &fileName);
  void Fail(const std::wstring &message, int64_t threadId,
            const std::wstring &fileName);
  void Write(const std::wstring &level, const std::wstring &message,
             int64_t threadId, const std::wstring &fileName);

  void Clear();
  json::value ToJSON();

private:
  std::mutex mMutex;

  std::wstring mSource;
  std::wstring mVersion;

  int32_t mIndex = 0;
  int32_t mMaxMessages = 0;
  LogMessage **mMessages = nullptr;
};
} // namespace Logger
