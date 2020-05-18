/*
    module  : setecho.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef SETECHO_C
#define SETECHO_C

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
