/*
    module  : __memoryindex.c
    version : 1.12
    date    : 06/29/22
*/
#ifndef __MEMORYINDEX_C
#define __MEMORYINDEX_C

/**
__memoryindex  :  ->  I
Pushes current value of memory.
*/
PRIVATE void do___memoryindex(pEnv env)
{
    COMPILE;
    PUSH_NUM(INTEGER_, GC_get_heap_size());
}
#endif
