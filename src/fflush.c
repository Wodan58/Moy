/*
    module  : fflush.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef FFLUSH_C
#define FFLUSH_C

/**
fflush  :  S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
PRIVATE void do_fflush(pEnv env)
{
    COMPILE;
    ONEPARAM("fflush");
    FILE("fflush");
    fflush(env->stk->u.fil);
}
#endif
