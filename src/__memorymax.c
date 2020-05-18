/*
    module  : __memorymax.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef __MEMORYMAX_C
#define __MEMORYMAX_C

/**
__memorymax  :  ->  I
Pushes value of total size of memory.
*/
PRIVATE void do___memorymax(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, MEMORYMAX);
}
#endif
