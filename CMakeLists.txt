cmake_minimum_required(VERSION 3.13)
project(Graphics C)

# set compiler standard to c99
set(CMAKE_C_STANDARD 99)

# set include dir and library dir to specific path
if (WIN32)
    set(SDL2_INCLUDE_DIR include)
    set(SDL2_LIBRARY_DIR lib/x64)
elseif (APPLE)
    set(SDL2_INCLUDE_DIR /usr/local/include)
    set(SDL2_LIBRARY_DIR /usr/local/lib)
endif ()

# add include and library dir to every add_executable
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY_DIR})

# add special compiler flags for better cross paltform code
set(CMAKE_C_FLAGS "-Wall -pedantic")

# add all headers
file(GLOB headers CONFIGURE_DEPENDS "header/*.h" "header/*.c")

# add executable
add_executable(heart ${headers} examples/heart.c)
add_executable(times_tables ${headers} examples/times_tables.c)
add_executable(tree ${headers} examples/tree.c)
add_executable(mandelbroatset_v2 ${headers} examples/mandelbroatset_v2.c)
add_executable(tic_tac_toe ${headers} examples/tic_tac_toe.c)
add_executable(menue ${headers} examples/menue.c)

if (WIN32)
    set(library_dependencies SDL2main SDL2 SDL2_ttf SDL2_image SDL2_mixer)
elseif (APPLE)
    set(library_dependencies SDL2 SDL2_ttf SDL2_image SDL2_mixer)
endif()

# link libraries during linking phase
target_link_libraries(heart ${library_dependencies})
target_link_libraries(times_tables ${library_dependencies})
target_link_libraries(tree ${library_dependencies})
target_link_libraries(mandelbroatset_v2 ${library_dependencies})
target_link_libraries(tic_tac_toe ${library_dependencies})
target_link_libraries(menue ${library_dependencies})

if (WIN32)
    # copy dlls to executable directory
    add_custom_target(copy_dll
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/${SDL2_LIBRARY_DIR}/SDL2.dll       ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/${SDL2_LIBRARY_DIR}/SDL2_image.dll ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/${SDL2_LIBRARY_DIR}/SDL2_ttf.dll   ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/${SDL2_LIBRARY_DIR}/SDL2_mixer.dll ${CMAKE_BINARY_DIR}
    )

    # add the copy_dll to every executable as a dependency
    add_dependencies(heart copy_dll)
    add_dependencies(times_tables copy_dll)
    add_dependencies(tree copy_dll)
    add_dependencies(mandelbroatset_v2 copy_dll)
    add_dependencies(tic_tac_toe copy_dll)
    add_dependencies(menue copy_dll)
endif (WIN32)
