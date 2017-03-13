/*
    module  : ldexp.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
ldexp  :  F I  ->  G
G is F times 2 to the Ith power.
*/
PRIVATE void do_ldexp(void)
{
    int exp;

#ifndef NCHECK
    if (optimizing && INTEGER_1 && NUMERIC_2)
	;
    else
	COMPILE;
    TWOPARAMS("ldexp");
    INTEGER("ldexp");
#endif
    exp = stk->u.num;
    POP(stk);
#ifndef NCHECK
    FLOAT("ldexp");
#endif
    if (OUTSIDE)
	stk->u.dbl = ldexp(FLOATVAL, exp);
    else
	UNARY(FLOAT_NEWNODE, ldexp(FLOATVAL, exp));
}
