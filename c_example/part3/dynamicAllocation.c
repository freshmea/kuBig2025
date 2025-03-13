#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int bookid;
    char bookname[40];
    char publisher[40];
    int price;
} Book;

int main(void)
{
    int size;
    scanf("%d", &size);
    int *pArr;
    pArr = (int *)malloc(sizeof(int) * size);

    srand(time(NULL));
    for (int i = 0; i < size; ++i)
    {
        *(pArr + i) = rand() % 101;
    }
    for (int i = 0; i < size; ++i)
    {
        printf("%d, ", *(pArr + i));
    }
    printf("\n");
    free(pArr);
    return 0;
}