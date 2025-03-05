#include <stdio.h>

int main(void)
{
    int man, woman;
    double sum, manRate, womanRate;

    // 입력 받는 코드
    printf("남자의 수는 : ");
    scanf("%d", &man);
    printf("여자의 수는 : ");
    scanf("%d", &woman);
    // 연산 하는 코드
    // 타입 캐스팅 sum = (double)man + (double)woman;
    sum = man + woman;
    womanRate = woman / sum * 100;
    manRate = man / sum * 100;

    printf("남자의 수는 %d명이고 여자의 수는 %d명이다.\n", man, woman);
    printf("총 수는 %.f명\n남자의 비율은 %.2f%%\n남자의 비율은 %.2f%%\n", sum, manRate, womanRate);
    return 0;
}