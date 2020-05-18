/*
    module  : ldexp.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef LDEXP_C
#define LDEXP_C

/**
ldexp  :  F I  ->  G
G is F times 2 to the Ith power.
*/
PRIVATE void do_ldexp(void)
{
    int exp;

#ifndef OLD_RUNTIME
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
    stk->u.dbl = ldexp(FLOATVAL, exp);
}
#endif
