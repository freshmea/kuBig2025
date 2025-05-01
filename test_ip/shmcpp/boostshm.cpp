// sudo apt-get install libboost-all-dev  # Ubuntu

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <cstring>
#include <iostream>

// 서버
int main()
{
    using namespace boost::interprocess;
    try
    {
        shared_memory_object shm(create_only, "myshm", read_write);
        shm.truncate(4096);
        mapped_region region(shm, read_write);
        std::strcpy(static_cast<char *>(region.get_address()), "Hello from server!");
        std::cout << "Server wrote message. Press Enter to exit...\n";
        std::cin.get();
        shared_memory_object::remove("myshm");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

// 클라이언트
int main()
{
    using namespace boost::interprocess;
    try
    {
        shared_memory_object shm(open_only, "myshm", read_only);
        mapped_region region(shm, read_only);
        std::cout << "Client read: " << static_cast<char *>(region.get_address()) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}