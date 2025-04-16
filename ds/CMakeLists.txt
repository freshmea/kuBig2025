cmake_minimum_required(VERSION 3.10)
project(kuBig2025_DS C)

# C 표준 설정
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# 디버그 모드 활성화
set(CMAKE_BUILD_TYPE Debug)

# 각 예제 폴더에 대한 실행 파일 설정
# strcpy 예제
add_executable(strcpy_test strcpy.c)

# list 예제들
add_executable(list_test list/main.c list/list.c)
add_executable(list2_test list2/main.c list2/list.c)
add_executable(list3_test list3/main.c list3/list.c)

# stack 예제들
add_executable(stack2_test stack2/main.c stack2/stack.c)
add_executable(stack3_test stack3/main.c stack3/stack.c)
add_executable(stack4_test stack4/main.c stack4/stack.c)
add_executable(stack5_test stack5/main.c stack5/stack.c)

# queue 예제들
add_executable(queue2_test queue2/main.c queue2/queue.c)
add_executable(queue3_test queue3/main.c queue3/queue.c)
add_executable(queue4_test queue4/main.c queue4/queue.c)
add_executable(queue5_test queue5/main.c queue5/queue.c)
add_executable(circular_queue_test circularQueue/main.c circularQueue/queue.c)

# 가변 크기 배열 예제
add_executable(var_size_array stack4/varSizeArray2.c)

# 단일 파일 예제
add_executable(list_example list.c)

# 모든 타겟에 대해 include 디렉토리 설정
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/list
    ${CMAKE_SOURCE_DIR}/list2
    ${CMAKE_SOURCE_DIR}/list3
    ${CMAKE_SOURCE_DIR}/stack2
    ${CMAKE_SOURCE_DIR}/stack3
    ${CMAKE_SOURCE_DIR}/stack4
    ${CMAKE_SOURCE_DIR}/stack5
    ${CMAKE_SOURCE_DIR}/queue2
    ${CMAKE_SOURCE_DIR}/queue3
    ${CMAKE_SOURCE_DIR}/queue4
    ${CMAKE_SOURCE_DIR}/queue5
    ${CMAKE_SOURCE_DIR}/circularQueue
)

# 컴파일 플래그 설정
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
endif()
