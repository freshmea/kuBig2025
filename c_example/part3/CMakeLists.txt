cmake_minimum_required(VERSION 3.10)
project(part3)

set(src_dir ${CMAKE_CURRENT_LIST_DIR})
file(GLOB EXECUTABLES "${src_dir}/*.c")

foreach(EXECUTABLE ${EXECUTABLES})
    get_filename_component(EXE_NAME ${EXECUTABLE} NAME_WE)
    add_executable(${EXE_NAME} ${EXECUTABLE})
endforeach()

# include 대신 add_subdirectory 사용
add_subdirectory(carSerial)
add_subdirectory(date)
add_subdirectory(myRandom)
add_subdirectory(string)