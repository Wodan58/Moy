/*
    module  : initmem.c
    version : 1.7
    date    : 03/12/17
*/
#include <stdio.h>
#include "joy.h"
#include "symbol.h"

void initmem(void)
{
    stk = &memory[MEMORYMAX];
    while (--stk > memory)
	stk->next = stk - 1;
    stk->next = memory;
}
