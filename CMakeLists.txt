cmake_minimum_required(VERSION 3.13)
project(Graphics C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-I/usr/local/include -lsdl2 -lsdl2_ttf -lsdl2_image -lsdl2_mixer -Wall -pedantic")

add_executable(heart header/window.c header/window.h header/graphics_helper.c header/graphics_helper.h heart.c)
add_executable(times_tables header/window.c header/window.h header/graphics_helper.c header/graphics_helper.h times_tables.c)
add_executable(tree header/window.c header/window.h header/graphics_helper.c header/graphics_helper.h tree.c)
add_executable(mandelbroatset_v2 header/window.c header/window.h header/graphics_helper.c header/graphics_helper.h mandelbroatset_v2.c)


