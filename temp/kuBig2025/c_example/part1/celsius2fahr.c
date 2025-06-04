/*
이 프로그램은 int 와 float 같의 연산을 데모하는 프로그램입니다.
이 프로그램은 최수길이 만들었습니다...
*/

#include <stdio.h>

int main()
{
    int celsius;
    // celsius = 15;
    printf("Input celsius temp: ?");
    scanf("%d", &celsius);
    printf("celsius temp : %d \n", celsius);

    double fahr;
    // 9 /5 를 하면 결과가 int 여서 1 이 된다.
    fahr = 9.0 / 5.0 * celsius + 32;
    printf("fahr temp : %f \n", fahr);

    return 0;
}