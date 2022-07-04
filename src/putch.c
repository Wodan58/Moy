/*
    module  : putch.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
PRIVATE void do_putch(pEnv env)
{
    COMPILE;
    ONEPARAM("putch");
    NUMERICTYPE("putch");
    printf("%c", (int)env->stk->u.num);
    POP(env->stk);
}
#endif
