@echo off

cmake -DBUILD_TOOLS=yes -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_TOOLCHAIN_FILE=C:/Users/koyanagi/github.com/microsoft/vcpkg/scripts/buildsystems/vcpkg.cmake ..
