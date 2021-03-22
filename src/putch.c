/*
    module  : putch.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
PRIVATE void do_putch(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("putch");
    NUMERICTYPE("putch");
    printf("%c", (int)env->stk->u.num);
    POP(env->stk);
}
#endif
