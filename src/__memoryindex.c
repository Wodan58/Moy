/*
    module  : __memoryindex.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef __MEMORYINDEX_C
#define __MEMORYINDEX_C

/**
__memoryindex  :  ->  I
Pushes current value of memory.
*/
PRIVATE void do___memoryindex(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, 0);
}
#endif
