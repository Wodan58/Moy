/*
    module  : __memorymax.c
    version : 1.6
    date    : 07/02/18
*/

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
