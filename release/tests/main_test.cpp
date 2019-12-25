#include <cpplogger/cpplogger.h>

int main() {
  Logger::Logger *l = new Logger::Logger(__key("source"), __key("version"), 8);
  l->Info(__key("test1"), 0, __LONGFILE__);
  l->Info(__key("test2"), 0, __LONGFILE__);
  l->Info(__key("test3"), 0, __LONGFILE__);

  if (l->IsEmpty()) {
    return -1;
  }

  json::value result;
  result = l->ToJSON();

  std::wcout << result.serialize().c_str() << std::endl;

  return 0;
}
