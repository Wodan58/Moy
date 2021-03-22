/*
    module  : __memoryindex.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef __MEMORYINDEX_C
#define __MEMORYINDEX_C

/**
__memoryindex  :  ->  I
Pushes current value of memory.
*/
PRIVATE void do___memoryindex(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, 0);
}
#endif
