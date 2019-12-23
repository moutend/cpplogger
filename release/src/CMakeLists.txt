file(GLOB HEADERS_CPPLOGGER"../include/cpplogger/*.h")
source_group("Header Files\\cpplogger" FILES ${HEADERS_CPPLOGGER})

set(SOURCES
  ${HEADERS_CPPAUDIO}
  cpplogger.cpp
)

add_library(cpplogger ${SOURCES})
target_include_directories(cpplogger PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
