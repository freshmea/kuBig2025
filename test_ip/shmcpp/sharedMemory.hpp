#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/mman.h>
#include <unistd.h>

class SharedMemory
{
public:
    // 생성자: 공유 메모리 생성 또는 열기
    SharedMemory(const std::string &name, size_t size, bool create)
        : name_(name), size_(size), shm_fd_(-1), data_(nullptr)
    {
        int flags = create ? O_CREAT | O_RDWR : O_RDWR;
        shm_fd_ = ::shm_open(name_.c_str(), flags, 0666);
        if (shm_fd_ == -1)
        {
            throw std::system_error(errno, std::system_category(), "shm_open failed");
        }

        if (create)
        {
            if (::ftruncate(shm_fd_, size_) == -1)
            {
                ::close(shm_fd_);
                throw std::system_error(errno, std::system_category(), "ftruncate failed");
            }
        }

        data_ = ::mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_, 0);
        if (data_ == MAP_FAILED)
        {
            ::close(shm_fd_);
            throw std::system_error(errno, std::system_category(), "mmap failed");
        }
    }

    // 소멸자: 자원 해제
    ~SharedMemory()
    {
        if (data_ != nullptr && data_ != MAP_FAILED)
        {
            ::munmap(data_, size_);
        }
        if (shm_fd_ != -1)
        {
            ::close(shm_fd_);
        }
    }

    // 공유 메모리에 데이터 쓰기
    void write(const std::string &message)
    {
        if (message.size() >= size_)
        {
            throw std::runtime_error("Message too large for shared memory");
        }
        std::memcpy(data_, message.c_str(), message.size() + 1); // Null 종료 포함
    }

    // 공유 메모리에서 데이터 읽기
    std::string read() const
    {
        return std::string(static_cast<char *>(data_));
    }

    // 공유 메모리 제거 (서버용)
    void unlink()
    {
        ::shm_unlink(name_.c_str());
    }

private:
    std::string name_;
    size_t size_;
    int shm_fd_;
    void *data_;
};