#include "sharedMemory.hpp"
#include <iostream>

int main()
{
    try
    {
        // 공유 메모리 열기 (이름: /myshm, 크기: 4096 바이트)
        SharedMemory shm("/myshm", 4096, false);

        // 메시지 읽기
        std::string message = shm.read();
        std::cout << "Client read: " << message << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}