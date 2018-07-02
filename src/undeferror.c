/*
    module  : undeferror.c
    version : 1.6
    date    : 07/02/18
*/

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
