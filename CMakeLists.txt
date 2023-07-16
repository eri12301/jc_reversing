cmake_minimum_required(VERSION 3.14)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/deps/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project(jade-cocoon VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out")
find_package(fmt CONFIG REQUIRED)
# Dependencies and Libraries
# includes relative to top level folder
include_directories(./)

add_executable(jc extractor/tiy_extractor.cpp)
target_link_libraries(jc PRIVATE fmt::fmt)