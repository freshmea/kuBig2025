cmake_minimum_required(VERSION 3.10)
project(MainProject)

# 내부 CMakeLists.txt 포함
include(sqlQuery/CMakeLists.txt)
include(c_example/part1/CMakeLists.txt)
include(c_example/part2/CMakeLists.txt)
include(c_example/part3/CMakeLists.txt)