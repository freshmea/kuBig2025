#include <limits.h>
#include <stdio.h>

void printHello();

// int main(int argc, char* argv[]) 인수를 받을 때
int main(void)
{
    printHello();
    printf("char_bit : %d\n", CHAR_BIT);
    printf("char_max : %d\n", CHAR_MAX);
    printf("INT_MIN : %d \t INT_MAX : %d\n", INT_MIN, INT_MAX);
    printf("LONG_MIN : %ld \t LONG_MAX : %ld\n", LONG_MIN, LONG_MAX);
    // printf("INT_MAX + 1 : %d\n", INT_MAX + 1);
#if __STDC_VERSION__ >= 201112L
    printf("C11 또는 그 이상\n");
#elif __STDC_VERSION__ >= 199901L
    printf("C99\n");
#else
    printf("C89/C90\n");
#endif
    return 0;
}

void printHello()
{
    printf("hello, world\n");
}
