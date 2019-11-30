cmake_minimum_required(VERSION 3.12)
project(
  cpplogger
  VERSION 0.1.0
  DESCRIPTION "Tiny logger library based on string stream."
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(
  LIBRARY_SOURCES
  src/cpplogger.h
  src/cpplogger.cpp
)
add_library(cpplogger ${LIBRARY_SOURCES})
