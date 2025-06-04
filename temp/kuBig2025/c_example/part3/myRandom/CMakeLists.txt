cmake_minimum_required(VERSION 3.10)
project(myRandom)

# 소스 파일 설정
set(SOURCES
    main.c
    myRandom.c
)

include_directories(${CMAKE_CURRENT_LIST_DIR})
add_executable(myRandom ${SOURCES})