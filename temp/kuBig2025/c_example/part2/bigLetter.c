// 임이의 char를 scanf 로 하나 받아서 대문자 인지 소문자인지 출력하세요.
#include <stdio.h>

int main(void)
{
    char ch;
    printf("문자를 하나 넣으세요 :");
    scanf("%c", &ch);

    if ('A' <= ch && ch <= 'Z')
    {
        printf("%c 는 대문자 입니다.\n", ch);
    }
    else if ('a' <= ch && ch <= 'z')
    {
        printf("%c 는 소문자 입니다.\n", ch);
    }
    else
    {
        printf("%c 는 영문자가 아닙니다.\n", ch);
    }
    return 0;
}
