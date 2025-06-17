cmake_minimum_required(VERSION 3.0)
project(OpenCV_part6)

find_package(OpenCV REQUIRED)

add_executable(59_minist 59_minist.cpp)
target_link_libraries(59_minist ${OpenCV_LIBS})


