
# https://github.com/Isty001/dotenv-c.git 이 깃을 사용하여 dotenv를 사용하였습니다.
cmake_minimum_required(VERSION 3.10)
project(bowling)

set(SOURCES
    src/bowling.c
    src/board.c
    src/main.c
    src/bowlingsql.c

)

add_executable(bowling ${SOURCES})
target_include_directories(bowling PRIVATE include)

# library setting
target_include_directories(bowling PRIVATE /usr/include/mysql)
target_link_directories(bowling PRIVATE /usr/lib/mysql)
target_link_libraries(bowling PRIVATE mysqlclient)
target_link_directories(bowling PRIVATE /usr/local/bin)
target_link_libraries(bowling PRIVATE dotenv)

# data file 추가 /src/.env
configure_file(src/.env .env COPYONLY)