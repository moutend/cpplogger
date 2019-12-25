#include <cpplogger/cpplogger.h>

int main() {
  Logger::Logger *l =
      new Logger::Logger(__ustring("source"), __ustring("version"), 3);
  if (!l->IsEmpty()) {
    return -1;
  }

  l->Info(__ustring("foo1"), 0, __LONGFILE__);
  l->Info(__ustring("foo2"), 0, __LONGFILE__);

  if (l->IsEmpty()) {
    return -1;
  }

  json::value result1 = l->ToJSON();

  if (result1[__ustring("messages")][0][__ustring("message")] !=
      json::value(__ustring("foo1"))) {
    return -1;
  }
  if (result1[__ustring("messages")][1][__ustring("message")] !=
      json::value(__ustring("foo2"))) {
    return -1;
  }

  return 0;
  l->Clear();

  if (!l->IsEmpty()) {
    return -1;
  }

  l->Warn(__ustring("bar1"), 0, __LONGFILE__);
  l->Warn(__ustring("bar2"), 0, __LONGFILE__);

  if (l->IsEmpty()) {
    return -1;
  }

  json::value result2 = l->ToJSON();

  if (result2[__ustring("messages")][0][__ustring("message")] !=
      json::value(__ustring("bar1"))) {
    return -1;
  }
  if (result2[__ustring("messages")][1][__ustring("message")] !=
      json::value(__ustring("bar2"))) {
    return -1;
  }

  return 0;
  l->Clear();

  if (!l->IsEmpty()) {
    return -1;
  }

  l->Fail(__ustring("foobar1"), 0, __LONGFILE__);
  l->Fail(__ustring("foobar2"), 0, __LONGFILE__);
  l->Fail(__ustring("foobar3"), 0, __LONGFILE__);
  l->Fail(__ustring("foobar4"), 0, __LONGFILE__);
  l->Fail(__ustring("foobar5"), 0, __LONGFILE__);

  if (l->IsEmpty()) {
    return -1;
  }

  json::value result3 = l->ToJSON();

  if (result3[__ustring("messages")][0][__ustring("message")] !=
      json::value(__ustring("foobar4"))) {
    return -1;
  }
  if (result3[__ustring("messages")][1][__ustring("message")] !=
      json::value(__ustring("foobar2"))) {
    return -1;
  }
  if (result3[__ustring("messages")][2][__ustring("message")] !=
      json::value(__ustring("foobar5"))) {
    return -1;
  }

  return 0;
}
