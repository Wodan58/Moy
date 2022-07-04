/*
    module  : fputch.c
    version : 1.11
    date    : 06/20/22
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

    COMPILE;
    TWOPARAMS("fputch");
    INTEGER("fputch");
    ch = env->stk->u.num;
    POP(env->stk);
    FILE("fputch");
    fputc(ch, env->stk->u.fil);
}
#endif
