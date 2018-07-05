/*
    module  : setecho.c
    version : 1.6
    date    : 07/05/18
*/

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
