/*
    module  : neg.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
neg  :  I  ->  J
Integer J is the negative of integer I.  Also supports float.
*/
/* neg.c */
PRIVATE void neg_(void)
{
    ONEPARAM("neg");
    FLOAT("neg");
    if (OUTSIDE) {
	if (stk->op == FLOAT_)
	    stk->u.dbl = -stk->u.dbl;
	else
	    stk->u.num = -stk->u.num;
    } else if (stk->op == FLOAT_)
	UNARY(FLOAT_NEWNODE, -stk->u.dbl);
    else if (stk->u.num)
	UNARY(INTEGER_NEWNODE, -stk->u.num);
}
