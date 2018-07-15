/*
    module  : __memorymax.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef __MEMORYMAX_X
#define __MEMORYMAX_C

#ifdef NEW_RUNTIME
PRIVATE void do___memorymax(void)
{
    TRACE;
#ifdef VECTOR
    do_push(vec_max(theStack));
#else
    do_push(MEMORYMAX);
#endif
}
#else
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
#endif
