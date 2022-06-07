include_directories(../data)
include_directories(../../libs/SDL2/x64/include)

add_library(cpu cpu.cpp cpu.h)
add_library(rom rom.cpp rom.h)
add_library(display display.cpp display.h)