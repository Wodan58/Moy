/*
    module  : memorymax.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
__memorymax  : ->  I
Pushes value of total size of memory.
*/
PRIVATE void do_memorymax(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, MEMORYMAX);
}
