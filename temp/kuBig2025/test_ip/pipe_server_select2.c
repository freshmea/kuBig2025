#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define NUM_PIPES 5
#define PIPE_PREFIX "/tmp/pipe"

// 파이프 경로와 파일 디스크립터를 관리하는 구조체
typedef struct
{
    char path[32];
    int fd;
} Pipe;

// 파이프 생성 함수
void create_pipe(const char *path)
{
    unlink(path); // 기존 파이프 제거
    if (mkfifo(path, 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
}

// 파이프 열기 함수
int open_pipe(const char *path)
{
    printf("%s 열기 시도\n", path);
    int fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd == -1)
    {
        perror("open pipe");
        exit(EXIT_FAILURE);
    }
    return fd;
}

// 파이프 읽기 및 메시지 출력 함수
void read_pipe(int fd, const char *path, char *buffer, size_t buf_size)
{
    ssize_t bytes_read = read(fd, buffer, buf_size - 1);
    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        printf("%s에서 읽은 메세지: %s", path, buffer);
    }
    else if (bytes_read == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
    {
        perror("read pipe");
    }
}

int main()
{
    Pipe pipes[NUM_PIPES];
    char buffer[BUFFER_SIZE];
    fd_set read_fds;
    struct timeval timeout;
    int max_fd = 0;

    // 파이프 경로 초기화 및 생성
    for (int i = 0; i < NUM_PIPES; i++)
    {
        snprintf(pipes[i].path, sizeof(pipes[i].path), "%s%d", PIPE_PREFIX, i + 1);
        create_pipe(pipes[i].path);
    }

    printf("클라이언트 기다림\n");

    // 파이프 열기
    for (int i = 0; i < NUM_PIPES; i++)
    {
        pipes[i].fd = open_pipe(pipes[i].path);
        if (pipes[i].fd > max_fd)
        {
            max_fd = pipes[i].fd;
        }
    }
    max_fd += 1;

    printf("메세지 수신 대기\n");
    while (1)
    {
        FD_ZERO(&read_fds);
        for (int i = 0; i < NUM_PIPES; i++)
        {
            FD_SET(pipes[i].fd, &read_fds);
        }
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
            for (int i = 0; i < NUM_PIPES; i++)
            {
                if (FD_ISSET(pipes[i].fd, &read_fds))
                {
                    read_pipe(pipes[i].fd, pipes[i].path, buffer, BUFFER_SIZE);
                }
            }
        }
    }

    // 정리
    for (int i = 0; i < NUM_PIPES; i++)
    {
        close(pipes[i].fd);
        unlink(pipes[i].path);
    }

    return 0;
}