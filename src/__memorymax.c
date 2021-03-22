/*
    module  : __memorymax.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef __MEMORYMAX_C
#define __MEMORYMAX_C

/**
__memorymax  :  ->  I
Pushes value of total size of memory.
*/
PRIVATE void do___memorymax(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, 0);
}
#endif
