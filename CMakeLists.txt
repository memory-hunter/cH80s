cmake_minimum_required(VERSION 3.22)
project(cH80s VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} src/chaos.cpp)

add_subdirectory(src)