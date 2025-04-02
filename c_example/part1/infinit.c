#include <stdio.h>
#include <unistd.h>

int main()
{
  while (1)
  {
    printf("process infinit!\n");
    fflush(stdout);
    sleep(1);
  }
  return 0;
}
