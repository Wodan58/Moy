/*
    module  : trunc.c
    version : 1.6
    date    : 07/02/18
*/

/**
trunc  :  F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
PRIVATE void do_trunc(void)
{
#ifndef NCHECK
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("trunc");
    FLOAT("trunc");
    if (OUTSIDE) {
	stk->u.num = FLOATVAL;
	stk->op = INTEGER_;
    } else
	UNARY(INTEGER_NEWNODE, (long_t) FLOATVAL);
}
