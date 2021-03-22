/*
    module  : fflush.c
    version : 1.9
    date    : 03/15/21
*/
#ifndef FFLUSH_C
#define FFLUSH_C

/**
fflush  :  S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
PRIVATE void do_fflush(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("fflush");
    FILE("fflush");
    fflush(env->stk->u.fil);
}
#endif
