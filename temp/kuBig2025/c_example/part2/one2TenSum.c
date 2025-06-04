#include <stdio.h>

int main(void)
{
    int sum = 0;

    for (int i = 0; i < 9901; ++i) // 9899 +100 9999
    {
        sum += i + 100;
    }
    // for (int i = 100; i <= 10000; ++i)
    // {
    //     sum += i;
    // }
    printf("100 부터 10000까지 더한 숫자는 %d 입니다.", sum);
    return 0;
}
