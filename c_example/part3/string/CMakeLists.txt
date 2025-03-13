cmake_minimum_required(VERSION 3.00)
project(myString)

# 현재 CMakeLists.txt가 위치한 디렉토리 경로 설정
set(src_dir ${CMAKE_CURRENT_LIST_DIR})

# 소스 파일 설정
set(SOURCES
    ${src_dir}/main.c
    ${src_dir}/myString.c
)

include_directories(${src_dir})
add_executable(myString ${SOURCES})