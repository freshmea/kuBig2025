cmake_minimum_required(VERSION 3.00)
project(carSerial)

# 현재 CMakeLists.txt가 위치한 디렉토리 경로 설정
set(carSerial_src_dir ${CMAKE_CURRENT_LIST_DIR})

# 소스 파일 설정
set(SOURCES
    ${carSerial_src_dir}/main.c
    ${carSerial_src_dir}/serial.c
)

include_directories(${carSerial_src_dir})
add_executable(carSerial ${SOURCES})