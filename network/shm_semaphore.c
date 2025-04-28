
// ps aux
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define SHM_NAME "/myshm"
#define SEM_NAME "/mysem"
#define SHM_SIZE 128

int main()
{
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);
    char *shm = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    pid_t pid = fork();
    if (pid == 0)
    {
        printf("부모");
    }
    if (pid == 1)
    {
        printf("자식");
    }
    getchar();

    munmap(shm, SHM_SIZE); // 메모리 해제
    close(shm_fd);
    shm_unlink(SHM_NAME); // 언링크

    sem_close(sem); // 세마포어 해제
    sem_unlink(SEM_NAME);

    return 0;
}