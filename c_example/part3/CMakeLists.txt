cmake_minimum_required(VERSION 3.10)
project(part3)

# 모든 .c 파일 자동 감지
file(GLOB EXECUTABLES "${CMAKE_CURRENT_LIST_DIR}/*.c")

foreach(EXECUTABLE ${EXECUTABLES})
    get_filename_component(EXE_NAME ${EXECUTABLE} NAME_WE)
    add_executable(${EXE_NAME} ${EXECUTABLE})
endforeach()

# 하위 디렉토리 추가
add_subdirectory(carSerial)
add_subdirectory(date)
add_subdirectory(myRandom)
add_subdirectory(string)