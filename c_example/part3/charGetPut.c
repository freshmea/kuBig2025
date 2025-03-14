// fgetc 예제
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char ch;
    char str[100];
    // fgetc(stdin)은 표준 입력 스트림(stdin)으로부터 문자를 읽어온다.
    // 버퍼가 비어있으면 입력을 기다린다.
    // 버퍼가 차 있으면 버퍼에서 문자를 하나만 읽어온다. 나머지는 계속 버퍼에 남아있다.
    printf("문자를 입력하세요: ");
    // ch = fgetc(stdin); // 입력할 문자열  slkajhsdlikcvjhqa
    ch = getc(stdin);
    printf("입력한 문자는 %c입니다.\n", ch);
    // 버퍼 비우기
    // fgetc 와 getchar 와의 차이는 getchar는 stdin을 인자로 받지 않아도 stdin 으로 설정 되어 있다.
    // fgetc 와 getc 의 차이는 동작 방식이 함수나 매크로냐의 차이다.
    // 그래서 기능상 차이는 없지만 속도면에서 차이가 있을 수 있다.
    while (getchar() != '\n')
        ;
    ch = fgetc(stdin);
    printf("입력한 문자는 %c입니다.\n", ch);
    scanf("%s", str);
    printf("입력한 문자열은 %s입니다.\n", str);
    return 0;
}