/*
    module  : trunc.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef TRUNC_C
#define TRUNC_C

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
    stk->u.num = FLOATVAL;
    stk->op = INTEGER_;
}
#endif
