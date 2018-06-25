/*
    module  : __memoryindex.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
__memoryindex  :  ->  I
Pushes current value of memory.
*/
PRIVATE void do___memoryindex(void)
{
    ptrdiff_t mem_index = 0;

#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    if (INSIDE)
	mem_index = stk - memory;
    PUSH(INTEGER_, mem_index);
}
