file(GLOB HEADERS_CPPLOGGER"../include/cpplogger/*.h")
source_group("Header Files\\cpplogger" FILES ${HEADERS_CPPLOGGER})

set(SOURCES
  ${HEADERS_CPPAUDIO}
  cpplogger.cpp
)

find_package(cpprestsdk REQUIRED NAMES cpprestsdk cpprest)

add_library(cpplogger ${SOURCES})
target_include_directories(cpplogger PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_link_libraries(cpplogger PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal)
