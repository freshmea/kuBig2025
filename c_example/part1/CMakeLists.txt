cmake_minimum_required(VERSION 3.10)
project(part1)

# set(EXECUTABLES
#     c_example/part1/infinit.c
#     c_example/part1/limit.c
#     c_example/part1/celsius2fahr.c
#     c_example/part1/fahr2celsius.c
#     c_example/part1/charNumber.c
#     c_example/part1/triangle.c
#     c_example/part1/triangle2.c
#     c_example/part1/arithmetics.c
#     c_example/part1/increment.c
#     c_example/part1/literal.c
#     c_example/part1/genderRatio.c
#     c_example/part1/compare.c
#     c_example/part1/compare2.c
#     c_example/part1/sizeof.c
#     c_example/part1/oddeven.c
#     c_example/part1/fourBit.c
#     c_example/part1/fourBit2.c
# )
file(GLOB EXECUTABLES "c_example/part1/*.c")

foreach(EXECUTABLE ${EXECUTABLES})
    get_filename_component(EXE_NAME ${EXECUTABLE} NAME_WE)
    add_executable(${EXE_NAME} ${EXECUTABLE})
endforeach()