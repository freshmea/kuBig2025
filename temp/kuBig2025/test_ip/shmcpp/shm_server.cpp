#include "sharedMemory.hpp"
#include <iostream>
#include <string>

int main()
{
    try
    {
        // 공유 메모리 생성 (이름: /myshm, 크기: 4096 바이트)
        SharedMemory shm("/myshm", 4096, true);

        // 메시지 쓰기
        std::string message = "Hello shared memory FROM process 1!";
        shm.write(message);
        std::cout << "Server wrote: " << message << std::endl;

        // 사용자 입력 대기 (종료 신호)
        std::cout << "Press Enter to exit..." << std::endl;
        std::string temp;
        std::getline(std::cin, temp);

        // 공유 메모리 제거
        shm.unlink();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}