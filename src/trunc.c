/*
    module  : trunc.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef TRUNC_C
#define TRUNC_C

/**
trunc  :  F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
PRIVATE void do_trunc(pEnv env)
{
    ONEPARAM("trunc");
    FLOAT("trunc");
    UNARY(INTEGER_NEWNODE, (long)FLOATVAL);
}
#endif
