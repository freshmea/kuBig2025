#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define PIPE1 "/tmp/pipe1" // 서버 -> 클라이언트
#define PIPE2 "/tmp/pipe2" // 클라이언트 -> 서버

int main()
{
    int fd1, fd2;
    char buffer[BUFFER_SIZE];

    mkfifo(PIPE1, 0666);
    mkfifo(PIPE2, 0666);

    fd1 = open(PIPE1, O_WRONLY);
    fd2 = open(PIPE2, O_RDONLY);

    char *message = "Hello from Parent!";
    write(fd1, message, strlen(message) + 1);
    printf("서버에서 보낸 메세지: %s\n", message);
    getchar();
    read(fd2, buffer, BUFFER_SIZE); // 대기
    printf("서버에서 읽은 메세지: %s\n", buffer);
    close(fd1);
    close(fd2);

    unlink(PIPE1);
    unlink(PIPE2);

    return 0;
}