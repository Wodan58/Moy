/*
    module  : fputch.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef FPUTCH_C
#define FPUTCH_C

/**
fputch  :  S C  ->  S
The character C is written to the current position of stream S.
*/
PRIVATE void do_fputch(pEnv env)
{
    int ch;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    TWOPARAMS("fputch");
    INTEGER("fputch");
    ch = env->stk->u.num;
    POP(env->stk);
    FILE("fputch");
    putc(ch, env->stk->u.fil);
}
#endif
