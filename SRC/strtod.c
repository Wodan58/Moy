/*
    module  : strtod.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
strtod  :  S  ->  R
String S is converted to the float R.
*/
/* strtod.c */
PRIVATE void strtod_(void)
{
    ONEPARAM("strtod");
    STRING("strtod");
    if (OUTSIDE) {
	stk->u.num = strtod(stk->u.str, 0);
	stk->op = FLOAT_;
    } else
	UNARY(FLOAT_NEWNODE, strtod(stk->u.str, 0));
}
