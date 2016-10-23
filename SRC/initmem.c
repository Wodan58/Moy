/*
    module  : initmem.c
    version : 1.6
    date    : 10/17/16
*/
#include <stdio.h>
#include <time.h>
#include "globals1.h"

void initmem(void)
{
    for (stk = memory; stk < &memory[MEMORYMAX]; stk++)
	stk->next = stk + 1;
    stk->mark = 1;
    stk->next = stk;
}
