/*
    module  : initmem.c
    version : 1.2
    date    : 09/09/16
*/
#include <stdio.h>
#include <time.h>
#include "globals1.h"

void initmem(void)
{
    for (stk = memory; stk < &memory[MEMORYMAX]; stk++)
	stk->next = stk + 1;
    stk = stk->next = &memory[MEMORYMAX];
    crit_ptr = &critical[MEMORYMAX];
}
