/*
    module  : __memorymax.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
__memorymax  :  ->  I
Pushes value of total size of memory.
*/
PRIVATE void do___memorymax(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, MEMORYMAX);
}
