#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    int shm_fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 4096);
    char *shm = mmap(0, 4096, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);

    strcpy(shm, "Hello shared memory FROM process 1!");
    char temp[10];
    scanf("%s", temp);
    munmap(shm, 4096);
    shm_unlink("/myshm");
    return 0;
}