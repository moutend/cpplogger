add_executable(parallel_test main_test.cpp)
target_link_libraries(parallel_test cpplogger)
add_test(
  NAME parallel_test
  COMMAND $<TARGET_FILE:parallel_test>
)
