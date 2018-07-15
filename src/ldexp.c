/*
    module  : ldexp.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef LDEXP_X
#define LDEXP_C

#ifdef NEW_RUNTIME
void do_ldexp(void)
{
    int exp;
    float dbl;

    TRACE;
    exp = do_pop();
    memcpy(&dbl, &stk[-1], sizeof(float));
    dbl = ldexp(dbl, exp);
    memcpy(&stk[-1], &dbl, sizeof(node_t));
}
#else
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
    if (OUTSIDE)
	stk->u.dbl = ldexp(FLOATVAL, exp);
    else
	UNARY(FLOAT_NEWNODE, ldexp(FLOATVAL, exp));
}
#endif
#endif
