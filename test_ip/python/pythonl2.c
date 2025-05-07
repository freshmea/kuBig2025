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
    char arg[256]; // 출력할 문자열
} Instruction;

// 파서: print("내용") 형태를 인식하여 내용만 추출
Instruction parse(const char *source)
{
    Instruction inst;
    inst.opcode = OP_UNKNOWN;
    inst.arg[0] = '\0';

    // print로 시작하고 괄호 및 큰따옴표 있는지 확인
    const char *prefix = "print(\"";
    size_t prefix_len = strlen(prefix);

    if (strncmp(source, prefix, prefix_len) == 0)
    {
        const char *end_quote = strchr(source + prefix_len, '"'); // 종료 따옴표 위치
        const char *end_paren = strchr(end_quote ? end_quote + 1 : NULL, ')');

        if (end_quote && end_paren)
        {
            size_t len = end_quote - (source + prefix_len);
            if (len < sizeof(inst.arg))
            {
                strncpy(inst.arg, source + prefix_len, len);
                inst.arg[len] = '\0';
                inst.opcode = OP_PRINT;
            }
        }
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

// main 함수
int main()
{
    char source[512];

    printf("Mini Python Interpreter (type: print(\"something\"))\n> ");
    fgets(source, sizeof(source), stdin);

    // 줄 끝 개행 문자 제거
    source[strcspn(source, "\n")] = 0;

    // 파싱 → 실행
    Instruction inst = parse(source);
    execute(inst);

    return 0;
}
