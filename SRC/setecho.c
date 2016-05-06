/*
    module  : setecho.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
setecho  :  I  ->
Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
/* setecho.c */
USETOP(setecho_, "setecho", NUMERICTYPE, echoflag = stk->u.num)
