#include "date.h"

int main(void)
{
    Date d;
    d.year = 2025;
    d.month = 3;
    d.day = 11;

    Date today;
    today = d;
    printDate(&today);

    return 0;
}