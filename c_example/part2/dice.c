// 난수를 이용해서 1~6 까지의 숫자를 만들기
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int dice[30];
    srand(time(NULL));
    // 배열에 값을 넣기
    for (int i = 0; i < 30; ++i)
    {
        dice[i] = rand() % 6 + 1;
        printf("%d ,", dice[i]);
        printf("%p ", &dice[i]);
    }
    printf("\n");
    // 각 배열을 변경 - 10을 곱하기
    for (int i = 0; i < 30; ++i)
    {
        dice[i] *= 10;
        printf("%d ,", dice[i]);
        printf("%p ", &dice[i]);
    }
    printf("\n");
    return 0;
}