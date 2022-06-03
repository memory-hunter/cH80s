cmake_minimum_required(VERSION 3.22)
project(cH80s VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} src/chaos.cpp)

add_subdirectory(src)

target_link_directories(${PROJECT_NAME}
        PRIVATE core
        PRIVATE data
        )

target_link_libraries(${PROJECT_NAME}
        cpu
        data
        rom
        )