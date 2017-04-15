/*
    module  : memoryindex.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
__memoryindex  :  ->  I
Pushes current value of memory.
*/
PRIVATE void do_memoryindex(void)
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
