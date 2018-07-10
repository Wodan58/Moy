/*
    module  : __memorymax.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef __MEMORYMAX_X
#define __MEMORYMAX_C

#ifdef RUNTIME
PRIVATE void do___memorymax(void)
{
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
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, MEMORYMAX);
}
#endif
#endif
