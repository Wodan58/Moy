/*
    module  : fputchars.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef FPUTCHARS_C
#define FPUTCHARS_C

/**
fputchars  :  S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
PRIVATE void do_fputchars(pEnv env)
{
    char *str;

    COMPILE;
    TWOPARAMS("fputchars");
    str = env->stk->u.str;
    POP(env->stk);
    FILE("fputchars");
    fprintf(env->stk->u.fil, "%s", str);
}
#endif
