#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define PIPE1 "/tmp/pipe1"
#define PIPE2 "/tmp/pipe2"
#define PIPE3 "/tmp/pipe3"
#define PIPE4 "/tmp/pipe4"
#define PIPE5 "/tmp/pipe5"

int main()
{
    int fd1, fd2, fd3, fd4, fd5;
    char buffer[BUFFER_SIZE];

    // 기존 파이프 제거
    unlink(PIPE1);
    unlink(PIPE2);
    unlink(PIPE3);
    unlink(PIPE4);
    unlink(PIPE5);

    // 파이프 생성
    if (mkfifo(PIPE1, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo pipe1");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(PIPE2, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo pipe2");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(PIPE3, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo pipe3");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(PIPE4, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo pipe4");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(PIPE5, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo pipe5");
        exit(EXIT_FAILURE);
    }

    printf("클라이언트 기다림\n");

    // 파이프 열기 (논블록 읽기 모드)
    printf("pipe1 열기 시도\n");
    fd1 = open(PIPE1, O_RDONLY | O_NONBLOCK);
    if (fd1 == -1)
    {
        perror("open pipe1");
        exit(EXIT_FAILURE);
    }
    printf("pipe2 열기 시도\n");
    fd2 = open(PIPE2, O_RDONLY | O_NONBLOCK);
    if (fd2 == -1)
    {
        perror("open pipe2");
        exit(EXIT_FAILURE);
    }
    printf("pipe3 열기 시도\n");
    fd3 = open(PIPE3, O_RDONLY | O_NONBLOCK);
    if (fd3 == -1)
    {
        perror("open pipe3");
        exit(EXIT_FAILURE);
    }
    printf("pipe4 열기 시도\n");
    fd4 = open(PIPE4, O_RDONLY | O_NONBLOCK);
    if (fd4 == -1)
    {
        perror("open pipe4");
        exit(EXIT_FAILURE);
    }
    printf("pipe5 열기 시도\n");
    fd5 = open(PIPE5, O_RDONLY | O_NONBLOCK);
    if (fd5 == -1)
    {
        perror("open pipe5");
        exit(EXIT_FAILURE);
    }

    // select 설정
    fd_set read_fds;
    struct timeval timeout;
    int max_fd = fd1;
    if (fd2 > max_fd)
        max_fd = fd2;
    if (fd3 > max_fd)
        max_fd = fd3;
    if (fd4 > max_fd)
        max_fd = fd4;
    if (fd5 > max_fd)
        max_fd = fd5;
    max_fd += 1;

    printf("메세지 수신 대기\n");
    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(fd1, &read_fds);
        FD_SET(fd2, &read_fds);
        FD_SET(fd3, &read_fds);
        FD_SET(fd4, &read_fds);
        FD_SET(fd5, &read_fds);
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        int result = select(max_fd, &read_fds, NULL, NULL, &timeout);
        if (result == -1)
        {
            perror("select");
            break;
        }
        else if (result == 0)
        {
            printf("Time out!\n");
            break;
        }
        else
        {
            if (FD_ISSET(fd1, &read_fds))
            {
                ssize_t bytes_read = read(fd1, buffer, BUFFER_SIZE - 1);
                if (bytes_read > 0)
                {
                    buffer[bytes_read] = '\0';
                    printf("파이프1에서 읽은 메세지: %s", buffer);
                }
                else if (bytes_read == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
                {
                    perror("read pipe1");
                }
            }
            if (FD_ISSET(fd2, &read_fds))
            {
                ssize_t bytes_read = read(fd2, buffer, BUFFER_SIZE - 1);
                if (bytes_read > 0)
                {
                    buffer[bytes_read] = '\0';
                    printf("파이프2에서 읽은 메세지: %s", buffer);
                }
                else if (bytes_read == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
                {
                    perror("read pipe2");
                }
            }
            if (FD_ISSET(fd3, &read_fds))
            {
                ssize_t bytes_read = read(fd3, buffer, BUFFER_SIZE - 1);
                if (bytes_read > 0)
                {
                    buffer[bytes_read] = '\0';
                    printf("파이프3에서 읽은 메세지: %s", buffer);
                }
                else if (bytes_read == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
                {
                    perror("read pipe3");
                }
            }
            if (FD_ISSET(fd4, &read_fds))
            {
                ssize_t bytes_read = read(fd4, buffer, BUFFER_SIZE - 1);
                if (bytes_read > 0)
                {
                    buffer[bytes_read] = '\0';
                    printf("파이프4에서 읽은 메세지: %s", buffer);
                }
                else if (bytes_read == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
                {
                    perror("read pipe4");
                }
            }
            if (FD_ISSET(fd5, &read_fds))
            {
                ssize_t bytes_read = read(fd5, buffer, BUFFER_SIZE - 1);
                if (bytes_read > 0)
                {
                    buffer[bytes_read] = '\0';
                    printf("파이프5에서 읽은 메세지: %s", buffer);
                }
                else if (bytes_read == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
                {
                    perror("read pipe5");
                }
            }
        }
    }

    // 정리
    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);
    close(fd5);
    unlink(PIPE1);
    unlink(PIPE2);
    unlink(PIPE3);
    unlink(PIPE4);
    unlink(PIPE5);

    return 0;
}