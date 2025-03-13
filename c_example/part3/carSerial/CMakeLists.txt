cmake_minimum_required(VERSION 3.10)
project(carSerial)

# 소스 파일 설정
set(SOURCES
    main.c
    serial.c
)

add_executable(carSerial ${SOURCES})