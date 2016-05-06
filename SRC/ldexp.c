/*
    module  : ldexp.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
ldexp  :  F I  ->  G
G is F times 2 to the Ith power.
*/
/* ldexp.c */
PRIVATE void ldexp_(void)
{
    int exp;

    TWOPARAMS("ldexp");
    INTEGER("ldexp");
    exp = stk->u.num;
    POP(stk);
    FLOAT("ldexp");
    if (OUTSIDE)
	stk->u.dbl = ldexp(FLOATVAL, exp);
    else
	UNARY(FLOAT_NEWNODE, ldexp(FLOATVAL, exp));
}
