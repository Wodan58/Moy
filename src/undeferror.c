/*
    module  : undeferror.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef UNDEFERROR_C
#define UNDEFERROR_C

/**
undeferror  :  ->  I
Pushes current value of undefined-is-error flag.
*/
PRIVATE void do_undeferror(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, undeferror);
}
#endif
