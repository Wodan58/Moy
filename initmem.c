/*
    module  : initmem.c
    version : 1.1
    date    : 12/27/15
*/
#include <stdio.h>
#include "globals1.h"

void initmem(void)
{
    for (stk = memory; stk < &memory[MEMORYMAX]; stk++)
	stk->next = stk + 1;
    memory[MEMORYMAX - 1].next = stk = 0;

    crit_ptr = &critical[MEMORYMAX];
}
