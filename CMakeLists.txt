cmake_minimum_required(VERSION 3.16)

project(Triangulate VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

include(CTest)
include(FetchContent)

add_subdirectory(apps)
add_subdirectory(src)
add_subdirectory(tests)

