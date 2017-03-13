/*
    module  : memoryindex.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
__memoryindex  :  ->
Pushes current value of memory.
*/
PRIVATE void do_memoryindex(void)
{
    ptrdiff_t mem_index = 0;

#ifndef NCHECK
    COMPILE;
#endif
    if (INSIDE)
	mem_index = stk - memory;
    PUSH(INTEGER_, mem_index);
}
