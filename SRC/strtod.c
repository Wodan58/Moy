/*
    module  : strtod.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
strtod  :  S  ->  R
String S is converted to the float R.
*/
PRIVATE void do_strtod(void)
{
#ifndef NCHECK
    if (optimizing)
	chg_history(FLOAT_);
    if (optimizing && STRING_1)
	;
    else
	COMPILE;
    ONEPARAM("strtod");
    STRING("strtod");
#endif
    if (OUTSIDE) {
	stk->u.num = strtod(stk->u.str, 0);
	stk->op = FLOAT_;
    } else
	UNARY(FLOAT_NEWNODE, strtod(stk->u.str, 0));
}
