cmake_minimum_required(VERSION 3.0)
project(OpenCV_part4)

# ZeroMQ 라이브러리 찾기
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)


# zmq_1 실행 파일 빌드
add_executable(zmq_server zmq_server.cpp)
target_link_libraries(zmq_server PRIVATE zmq)

# zmq_2 실행 파일 빌드
add_executable(zmq_client zmq_client.cpp)
target_link_libraries(zmq_client PRIVATE zmq)

# OpenCV 예제 코드 (기존에 있었다면 유지 또는 필요에 따라 수정)
# find_package(OpenCV REQUIRED)
# add_executable(opencv_example example.cpp)
# target_link_libraries(opencv_example PRIVATE ${OpenCV_LIBS})

