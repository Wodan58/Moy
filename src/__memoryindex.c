/*
    module  : __memoryindex.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef __MEMORYINDEX_X
#define __MEMORYINDEX_C

/**
__memoryindex  :  ->  I
Pushes current value of memory.
*/
PRIVATE void do___memoryindex(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, 0);
}
#endif
