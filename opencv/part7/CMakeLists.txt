cmake_minimum_required(VERSION 3.0)
project(OpenCV_part6)

find_package(OpenCV REQUIRED)

add_executable(59_minist_cnn 59_minist_cnn.cpp)
target_link_libraries(59_minist_cnn ${OpenCV_LIBS})


