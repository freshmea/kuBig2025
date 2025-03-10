// BigEndian, LittleEndian
#include <stdio.h>

int main(void)
{
    int a = 0x12345678;
    char *pA;
    pA = (char *)&a;
    printf("*pA : 0x%x\n", *pA);
    // 78 이 나오면 빅엔디안, 12가 나오면 리틀엔디안.
    return 0;
}
