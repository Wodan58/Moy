/*
    module  : abs.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
abs  :  N1  ->  N2
Integer N2 is the absolute value (0,1,2..) of integer N1,
or float N2 is the absolute value (0.0 ..) of float N1.
*/
/* abs.c */
PRIVATE void abs_(void)
{
    ONEPARAM("abs");
    FLOAT("abs");
    if (OUTSIDE) {
	if (stk->op == FLOAT_)
	    stk->u.dbl = fabs(stk->u.dbl);
	else if (stk->u.num < 0)
	    stk->u.num = -stk->u.num;
    } else if (stk->op == FLOAT_)
	UNARY(FLOAT_NEWNODE, fabs(stk->u.dbl));
    else if (stk->u.num < 0)
	UNARY(INTEGER_NEWNODE, -stk->u.num);
}
