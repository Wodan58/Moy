/*
    module  : undeferror.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef UNDEFERROR_X
#define UNDEFERROR_C

/**
undeferror  :  ->  I
Pushes current value of undefined-is-error flag.
*/
PRIVATE void do_undeferror(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, undeferror);
}
#endif
