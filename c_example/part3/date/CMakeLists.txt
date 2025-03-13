cmake_minimum_required(VERSION 3.00)
project(date)

# 현재 CMakeLists.txt가 위치한 디렉토리 경로 설정
set(date_src_dir ${CMAKE_CURRENT_LIST_DIR})

# 소스 파일 설정
set(SOURCES
    ${date_src_dir}/main.c
    ${date_src_dir}/date.c
)

include_directories(${date_src_dir})
add_executable(date ${SOURCES})