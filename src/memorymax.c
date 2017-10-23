/*
    module  : memorymax.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
__memorymax  :  ->  I
Pushes value of total size of memory.
*/
PRIVATE void do_memorymax(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, MEMORYMAX);
}
