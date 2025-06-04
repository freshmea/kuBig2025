#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    // 숫자 입력
    int num;
    int state;
    printf("숫자를 넣으세요: ");
    scanf("%d", &num);
    // 절대값 처리
    if (num < 0)
    {
        state = false;
    }
    else
    {
        state = true;
    }
    num = state ? num : -num;
    // 숫자 출력
    printf("주어진 숫자의 절대값은 %d 이다.\n", num);
    return 0;
}