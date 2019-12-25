add_executable(main_test main_test.cpp)
target_link_libraries(main_test cpplogger)
add_test(
  NAME main_test
  COMMAND $<TARGET_FILE:main_test>
)
