#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0) // 자식
    {
        puts("안녕, 자는 자식 프로세스야 !!");
    }
    else // 부모
    {
        printf("자식 프로세스 ID: %d \n", pid);
        sleep(30);
    }

    if (pid == 0)
        puts("End 자식 프로세스\n");
    else
        puts("End 부모 프로세스\n");

    return 0;
}