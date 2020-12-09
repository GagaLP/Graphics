cmake_minimum_required(VERSION 3.13)
project(Graphics C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-I/usr/local/include -L/usr/local/lib -lsdl2 -lsdl2_ttf -lsdl2_image -lsdl2_mixer -Wall -pedantic")

add_executable(heart header/window.c header/window.h header/graphics_helper.c header/graphics_helper.h examples/heart.c)
add_executable(times_tables header/window.c header/window.h header/graphics_helper.c header/graphics_helper.h examples/times_tables.c)
add_executable(tree header/window.c header/window.h header/graphics_helper.c header/graphics_helper.h examples/tree.c)
add_executable(mandelbroatset_v2 header/window.c header/window.h header/graphics_helper.c header/graphics_helper.h examples/mandelbroatset_v2.c)
add_executable(tic_tac_toe header/window.c header/window.h header/graphics_helper.c header/graphics_helper.h examples/tic_tac_toe.c)
