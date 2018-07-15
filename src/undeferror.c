/*
    module  : undeferror.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef UNDEFERROR_X
#define UNDEFERROR_C

#ifdef NEW_RUNTIME
void do_undeferror(void)
{
    TRACE;
    do_push(undeferror);
}
#else
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
#endif
