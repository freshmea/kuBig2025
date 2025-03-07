// 두 난수(0 ~ 100)를 발생 시켜서 비교하기
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int a, b;
    double rand1;
    srand((unsigned int)time(NULL));
    rand1 = rand() / (double)RAND_MAX * 100;
    printf("0 ~ 100 사이의 랜덤한 숫자: %f", rand1);
    return 0;
}