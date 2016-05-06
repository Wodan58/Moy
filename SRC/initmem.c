/*
    module  : initmem.c
    version : 1.1
    date    : 04/23/16
*/
#include <stdio.h>
#include <time.h>
#include "globals1.h"

void initmem(void)
{
    for (stk = memory; stk < &memory[MEMORYMAX]; stk++)
	stk->next = stk + 1;
    stk->next = &memory[MEMORYMAX];
    crit_ptr = &critical[MEMORYMAX];
}
