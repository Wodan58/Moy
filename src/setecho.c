/*
    module  : setecho.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef SETECHO_C
#define SETECHO_C

/**
setecho  :  I  ->
Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
PRIVATE void do_setecho(pEnv env)
{
#ifdef COMPILING
    ONEPARAM("setecho");
    NUMERICTYPE("setecho");
    setechoflag(env->stk->u.num);
    POP(env->stk);
#endif
}
#endif
