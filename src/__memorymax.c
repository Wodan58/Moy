/*
    module  : __memorymax.c
    version : 1.12
    date    : 06/29/22
*/
#ifndef __MEMORYMAX_C
#define __MEMORYMAX_C

/**
__memorymax  :  ->  I
Pushes value of total size of memory.
*/
PRIVATE void do___memorymax(pEnv env)
{
    COMPILE;
    PUSH_NUM(INTEGER_, GC_get_memory_use());
}
#endif
