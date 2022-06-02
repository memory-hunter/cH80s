add_executable(${PROJECT_NAME} chaos.cpp)

add_subdirectory(core)
add_subdirectory(data)

target_link_directories(${PROJECT_NAME}
        PRIVATE cpu
        PRIVATE data
        )

target_link_libraries(${PROJECT_NAME}
        cpu
        data
        rom
        )