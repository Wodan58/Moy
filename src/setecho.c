/*
    module  : setecho.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
setecho  :  I  ->
Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
PRIVATE void do_setecho(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("setecho");
    NUMERICTYPE("setecho");
#endif
    echoflag = stk->u.num;
    POP(stk);
}