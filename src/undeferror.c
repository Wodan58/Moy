/*
    module  : undeferror.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef UNDEFERROR_C
#define UNDEFERROR_C

/**
undeferror  :  ->  I
Pushes current value of undefined-is-error flag.
*/
PRIVATE void do_undeferror(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, undeferror);
}
#endif
