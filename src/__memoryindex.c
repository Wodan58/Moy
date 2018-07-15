/*
    module  : __memoryindex.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef __MEMORYINDEX_X
#define __MEMORYINDEX_C

#ifdef NEW_RUNTIME
PRIVATE void do___memoryindex(void)
{
    TRACE;
#ifdef VECTOR
    do_push(vec_size(theStack));
#else
    do_push(stk - memory);
#endif
}
#else
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
#endif
