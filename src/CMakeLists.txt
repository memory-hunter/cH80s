add_subdirectory(core)
add_subdirectory(data)
add_subdirectory(utils)

target_include_directories(${PROJECT_NAME}
        PUBLIC ../libs/SDL2/x64/include
        PUBLIC core
        PUBLIC data
        PUBLIC utils
        )

target_link_directories(${PROJECT_NAME}
        PUBLIC ../libs/SDL2/x64/lib/
        PUBLIC core
        PUBLIC data
        PUBLIC utils
        )

target_link_libraries(${PROJECT_NAME}
        cpu
        data
        rom
        display
        timer
        mingw32
        SDL2main
        SDL2
        )