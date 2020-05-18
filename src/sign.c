/*
    module  : sign.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef SIGN_C
#define SIGN_C

/**
sign  :  N1  ->  N2
Integer N2 is the sign (-1 or 0 or +1) of integer N1,
or float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1.
*/
PRIVATE double fsgn(double f)
{
    if (f < 0)
	return -1.0;
    else if (f > 0)
	return 1.0;
    else
	return 0.0;
}

PRIVATE void do_sign(void)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("sign");
    FLOAT("sign");
    if (stk->op == FLOAT_)
	stk->u.dbl = fsgn(stk->u.dbl);
    else if (stk->u.num < 0 || stk->u.num > 1)
	stk->u.num = stk->u.num > 0 ? 1 : -1;
}
#endif
