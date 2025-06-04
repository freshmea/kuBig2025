#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define NUM_PIPES 5
#define PIPE_PREFIX "/tmp/pipe"
#define MAX_EVENTS 10

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

// 파이프 재오픈 및 epoll 재등록 함수
void reopen_pipe(Pipe *pipe, int epfd)
{
    close(pipe->fd);                  // 기존 파이프 닫기
    pipe->fd = open_pipe(pipe->path); // 파이프 재오픈
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.ptr = pipe;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, pipe->fd, &event) == -1)
    {
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
    }
    printf("%s 재오픈 완료\n", pipe->path);
}

int main()
{
    Pipe pipes[NUM_PIPES];
    char buffer[BUFFER_SIZE];
    int epfd;
    struct epoll_event event, events[MAX_EVENTS];

    // epoll 인스턴스 생성
    epfd = epoll_create1(0);
    if (epfd == -1)
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    // 파이프 경로 초기화 및 생성
    for (int i = 0; i < NUM_PIPES; i++)
    {
        snprintf(pipes[i].path, sizeof(pipes[i].path), "%s%d", PIPE_PREFIX, i + 1);
        create_pipe(pipes[i].path);
    }

    printf("클라이언트 기다림\n");

    // 파이프 열기 및 epoll 등록
    for (int i = 0; i < NUM_PIPES; i++)
    {
        pipes[i].fd = open_pipe(pipes[i].path);
        event.events = EPOLLIN;
        event.data.ptr = &pipes[i];
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, pipes[i].fd, &event) == -1)
        {
            perror("epoll_ctl");
            exit(EXIT_FAILURE);
        }
    }

    printf("메세지 수신 대기\n");
    while (1)
    {
        // 타임아웃 10초 (10000ms)
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, 10000);
        if (nfds == -1)
        {
            perror("epoll_wait");
            break;
        }
        else if (nfds == 0)
        {
            printf("Time out!\n");
            break;
        }
        else
        {
            for (int i = 0; i < nfds; i++)
            {
                Pipe *pipe = (Pipe *)events[i].data.ptr;
                if (events[i].events & EPOLLIN)
                {
                    read_pipe(pipe->fd, pipe->path, buffer, BUFFER_SIZE);
                }
                if (events[i].events & (EPOLLERR))
                {
                    fprintf(stderr, "%s에서 오류\n", pipe->path);
                    // 파이프 재오픈 및 epoll 재등록
                    // reopen_pipe(pipe, epfd);
                }
                if (events[i].events & (EPOLLHUP))
                {
                    fprintf(stderr, "%s에서 연결 종료\n", pipe->path);
                    // 파이프 재오픈 및 epoll 재등록
                    reopen_pipe(pipe, epfd);
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
    close(epfd);

    return 0;
}