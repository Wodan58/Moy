/*
    module  : trunc.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef TRUNC_X
#define TRUNC_C

#ifdef NEW_RUNTIME
void do_trunc(void)
{
    float dbl;

    TRACE;
    memcpy(&dbl, &stk[-1], sizeof(float));
    stk[-1] = (int)dbl;
}
#else
/**
trunc  :  F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
PRIVATE void do_trunc(void)
{
#ifndef OLD_RUNTIME
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
#endif
#endif
