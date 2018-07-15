/*
    module  : setecho.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef SETECHO_X
#define SETECHO_C

#ifdef NEW_RUNTIME
void do_setechoflag(void)
{
    TRACE;
    setechoflag(do_pop());
}
#else
/**
setecho  :  I  ->
Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
PRIVATE void do_setecho(void)
{
    ONEPARAM("setecho");
    NUMERICTYPE("setecho");
    setechoflag(stk->u.num);
    POP(stk);
}
#endif
#endif
