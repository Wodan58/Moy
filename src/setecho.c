/*
    module  : setecho.c
    version : 1.5
    date    : 07/02/18
*/

/**
setecho  :  I  ->
Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
PRIVATE void do_setecho(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("setecho");
    NUMERICTYPE("setecho");
    setechoflag(stk->u.num);
    POP(stk);
}
