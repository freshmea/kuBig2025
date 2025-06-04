#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 바이트코드 종류 정의
typedef enum
{
    OP_PRINT,
    OP_UNKNOWN
} OpCode;

// 바이트코드 구조체
typedef struct
{
    OpCode opcode;
    const char *arg;
} Instruction;

// 간단한 파서: 문자열을 바이트코드로 변환
Instruction parse(const char *source)
{
    Instruction inst;
    if (strncmp(source, "print(\"hello\")", 15) == 0)
    {
        inst.opcode = OP_PRINT;
        inst.arg = "hello";
    }
    else
    {
        inst.opcode = OP_UNKNOWN;
        inst.arg = NULL;
    }
    return inst;
}

// 가상 머신 실행기
void execute(Instruction inst)
{
    switch (inst.opcode)
    {
    case OP_PRINT:
        printf("%s\n", inst.arg);
        break;
    default:
        printf("Unsupported instruction.\n");
        break;
    }
}

// main 함수: 인터프리터 역할
int main()
{
    char source[256];

    printf("Mini Python Interpreter (type: print(\"hello\"))\n> ");
    fgets(source, sizeof(source), stdin);

    // 줄 끝 개행 문자 제거
    source[strcspn(source, "\n")] = 0;

    // 파싱 → 실행
    Instruction inst = parse(source);
    execute(inst);

    return 0;
}
