#pragma once
#include <stdio.h>

typedef struct
{
    int year;
    int month;
    int day;
} Date;

void printDate(Date *);