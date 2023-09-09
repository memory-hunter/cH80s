find_package(SDL2 REQUIRED)
add_executable(${PROJECT_NAME} chaos.cpp)

if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src/include)
    target_include_directories(cH80s PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src/include)
    add_library(cpu STATIC cpu.cpp)
    add_library(rom STATIC rom.cpp)
    add_library(display STATIC display.cpp)
    add_library(data STATIC data.cpp)
    add_library(input STATIC input.cpp)
    add_library(timer STATIC timer.cpp)
    add_library(audio STATIC audio.cpp)
    target_link_libraries(cH80s PRIVATE ${SDL2_LIBRARIES} cpu data display rom input timer audio mingw32 SDL2main SDL2)
    set_target_properties(cH80s PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")
    if (WIN32)
        add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:cH80s>"
                VERBATIM
        )
    endif ()
endif ()