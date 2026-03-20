cmake_minimum_required(VERSION 3.10)
project(bowlingRay C)

set(SOURCES
    src/main.c
    src/bowling.c
    src/board.c
)

find_library(RAYLIB_LIBRARY NAMES raylib libraylib PATHS /usr/local/lib /usr/lib REQUIRED)

add_executable(bowlingRay ${SOURCES})
target_include_directories(bowlingRay PRIVATE include /usr/local/include /usr/include)
target_link_libraries(bowlingRay PRIVATE ${RAYLIB_LIBRARY} GL m pthread dl rt X11 c)