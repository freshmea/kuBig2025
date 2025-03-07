// 두 난수(0 ~ 100)를 발생 시켜서 비교하기
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int a, b;
    double rand1, rand2;
    srand((unsigned int)time(NULL)); // random 셋
    rand1 = rand() / (double)RAND_MAX * 100;
    srand((unsigned int)time(NULL) + 10000); // random 셋
    rand2 = rand() / (double)RAND_MAX * 100;

    a = rand1;
    b = rand2;
    printf("0 ~ 100 사이의 랜덤한 숫자: %f\n", rand1);
    printf("0 ~ 100 사이의 랜덤한 숫자: %f\n", rand2);
    printf("%d > %d : %s\n", a, b, a > b ? "true" : "false");
    printf("%d < %d : %s\n", a, b, a < b ? "true" : "false");
    printf("%d == %d : %s\n", a, b, a == b ? "true" : "false");
    printf("%d != %d : %s\n", a, b, a != b ? "true" : "false");

    return 0;
}