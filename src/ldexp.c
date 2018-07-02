/*
    module  : ldexp.c
    version : 1.6
    date    : 07/02/18
*/

/**
ldexp  :  F I  ->  G
G is F times 2 to the Ith power.
*/
PRIVATE void do_ldexp(void)
{
    int exp;

#ifndef NCHECK
    if (compiling && INTEGER_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
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
