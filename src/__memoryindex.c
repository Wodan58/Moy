/*
    module  : __memoryindex.c
    version : 1.6
    date    : 07/02/18
*/

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
