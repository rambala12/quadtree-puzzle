cmake_minimum_required(VERSION 2.8.8)
project(puzzle)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wno-varargs -Wno-char-subscripts")
include_directories(cimg)
if (APPLE OR UNIX)
    if (EXISTS /usr/X11R6)
        include_directories(/usr/X11R6/include)
        link_directories(/usr/X11R6/lib)
    endif()
endif(APPLE OR UNIX)

# add additional .cpp files to this executable
add_executable(puzzle main.cpp Puzzle.cpp QuadTree.cpp)
add_executable(scratch scratch.cpp Puzzle.cpp QuadTree.cpp)
if (APPLE OR UNIX)
    target_link_libraries(puzzle X11 pthread)
endif(APPLE OR UNIX)