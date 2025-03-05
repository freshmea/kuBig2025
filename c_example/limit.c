#include <limits.h>
#include <stdio.h>

void printHello();

// int main(int argc, char* argv[]) 인수를 받을 때
int main(void)
{
    printHello();
    printf("char_bit : %d\n", CHAR_BIT);
    printf("char_max : %d\n", CHAR_MAX);
    return 0;
}

void printHello()
{
    printf("hello, world\n");
}
