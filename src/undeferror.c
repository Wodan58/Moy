/*
    module  : undeferror.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef UNDEFERROR_C
#define UNDEFERROR_C

/**
undeferror  :  ->  I
Pushes current value of undefined-is-error flag.
*/
PRIVATE void do_undeferror(pEnv env)
{
    COMPILE;
    PUSH_NUM(INTEGER_, undeferror);
}
#endif
