#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void timeoutCallback(int sig);

int main()
{
    // signal(SIGALRM, timeoutCallback);   // 시그널이 발생하면 바로 다음루프
    struct sigaction act;
    act.sa_handler = timeoutCallback;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, 0);

    alarm(2);

    for (int i = 0; i < 10; ++i)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}

void timeoutCallback(int sig)
{
    if (sig == SIGALRM)
        puts("TIME out!");
    alarm(2);
}
