add_subdirectory(core)
add_subdirectory(data)

target_include_directories(${PROJECT_NAME}
        PUBLIC ../libs/SDL2/x64/include
        PUBLIC data
        )

target_link_directories(${PROJECT_NAME}
        PUBLIC core
        PUBLIC data
        PUBLIC ../libs/SDL2/x64/lib/
        )

target_link_libraries(${PROJECT_NAME}
        cpu
        data
        rom
        mingw32
        SDL2main
        SDL2
        )