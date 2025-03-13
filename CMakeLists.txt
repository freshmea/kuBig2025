cmake_minimum_required(VERSION 3.10)
project(MainProject)

# 내부 CMakeLists.txt 포함
include(sqlQuery/CMakeLists.txt)
include(c_example/part1/CmakeLists.txt)
# include(c_example/part2/CmakeLists.txt)
include(c_example/part3/CmakeLists.txt)