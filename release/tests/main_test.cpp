#include <cpplogger/cpplogger.h>

int main() {
  Logger::Logger *l = new Logger::Logger(__key("source"), __key("version"), 3);
  if (!l->IsEmpty()) {
    return -1;
  }

  l->Info(__key("foo1"), 0, __LONGFILE__);
  l->Info(__key("foo2"), 0, __LONGFILE__);

  if (l->IsEmpty()) {
    return -1;
  }

  json::value result1 = l->ToJSON();

  if (result1[__key("messages")][0][__key("message")] !=
      json::value(__key("foo1"))) {
    return -1;
  }
  if (result1[__key("messages")][1][__key("message")] !=
      json::value(__key("foo2"))) {
    return -1;
  }

  return 0;
  l->Clear();

  if (!l->IsEmpty()) {
    return -1;
  }

  l->Warn(__key("bar1"), 0, __LONGFILE__);
  l->Warn(__key("bar2"), 0, __LONGFILE__);

  if (l->IsEmpty()) {
    return -1;
  }

  json::value result2 = l->ToJSON();

  if (result2[__key("messages")][0][__key("message")] !=
      json::value(__key("bar1"))) {
    return -1;
  }
  if (result2[__key("messages")][1][__key("message")] !=
      json::value(__key("bar2"))) {
    return -1;
  }

  return 0;
  l->Clear();

  if (!l->IsEmpty()) {
    return -1;
  }

  l->Fail(__key("foobar1"), 0, __LONGFILE__);
  l->Fail(__key("foobar2"), 0, __LONGFILE__);
  l->Fail(__key("foobar3"), 0, __LONGFILE__);
  l->Fail(__key("foobar4"), 0, __LONGFILE__);
  l->Fail(__key("foobar5"), 0, __LONGFILE__);

  if (l->IsEmpty()) {
    return -1;
  }

  json::value result3 = l->ToJSON();

  if (result3[__key("messages")][0][__key("message")] !=
      json::value(__key("foobar4"))) {
    return -1;
  }
  if (result3[__key("messages")][1][__key("message")] !=
      json::value(__key("foobar2"))) {
    return -1;
  }
  if (result3[__key("messages")][2][__key("message")] !=
      json::value(__key("foobar5"))) {
    return -1;
  }

  return 0;
}
