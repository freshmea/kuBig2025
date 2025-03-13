cmake_minimum_required(VERSION 3.10)
project(part3)

set(src_dir ${CMAKE_CURRENT_LIST_DIR})
file(GLOB EXECUTABLES "${src_dir}/*.c")

foreach(EXECUTABLE ${EXECUTABLES})
    get_filename_component(EXE_NAME ${EXECUTABLE} NAME_WE)
    add_executable(${EXE_NAME} ${EXECUTABLE})
endforeach()

include(${src_dir}/carSerial/CMakeLists.txt)
include(${src_dir}/date/CMakeLists.txt)
include(${src_dir}/myRandom/CMakeLists.txt)
include(${src_dir}/string/CMakeLists.txt)