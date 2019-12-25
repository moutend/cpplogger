add_executable(serial_test main_test.cpp)
target_link_libraries(serial_test cpplogger)
add_test(
  NAME serial_test
  COMMAND $<TARGET_FILE:serial_test>
)
