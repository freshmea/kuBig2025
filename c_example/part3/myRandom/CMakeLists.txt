cmake_minimum_required(VERSION 3.00)
project(myRandom)

# 현재 CMakeLists.txt가 위치한 디렉토리 경로 설정
set(myRandom_src_dir ${CMAKE_CURRENT_LIST_DIR})

# 소스 파일 설정
set(SOURCES
    ${myRandom_src_dir}/main.c
    ${myRandom_src_dir}/myRandom.c
)

include_directories(${myRandom_src_dir})
add_executable(myRandom ${SOURCES})