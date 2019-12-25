#pragma once

#include <cpprest/details/basic_types.h>
#include <cpprest/json.h>
#include <cstdint>
#include <mutex>

#define __wcstringify2(x) L##x
#define __wcstringify1(x) __wcstringify2(x)
#define __cstringify2(x) #x
#define __cstringify1(x) __cstringify2(x)

#ifdef _UTF16_STRINGS
#define __ustring(x) L##x
#define __LONGFILE__                                                           \
  __wcstringify1(__FILE__) L":" __wcstringify1(__cstringify1(__LINE__))
#else
#define __ustring(x) x
#define __LONGFILE__ __FILE__ ":" __cstringify1(__LINE__)
#endif

using namespace web;

namespace Logger {
struct LogMessage {
  utility::string_t Level;
  utility::string_t Message;
  utility::string_t Path;
  int64_t ThreadId = 0;
  int64_t UnixTimestampSec = 0;
  int64_t UnixTimestampNano = 0;
};

class Logger {
public:
  Logger(const utility::string_t &source, const utility::string_t &version,
         int32_t maxMessages);
  ~Logger();

  void Info(const utility::string_t &message, int64_t threadId,
            const utility::string_t &fileName);
  void Warn(const utility::string_t &message, int64_t threadId,
            const utility::string_t &fileName);
  void Fail(const utility::string_t &message, int64_t threadId,
            const utility::string_t &fileName);
  void Write(const utility::string_t &level, const utility::string_t &message,
             int64_t threadId, const utility::string_t &fileName);

  void Clear();
  json::value ToJSON();

  bool IsEmpty();
  void Lock();
  void Unlock();

private:
  std::mutex mMutex;

  utility::string_t mSource;
  utility::string_t mVersion;

  int32_t mMessageCount = 0;
  int32_t mIndex = 0;
  int32_t mMaxMessages = 0;

  LogMessage *mMessages = nullptr;
};
} // namespace Logger
