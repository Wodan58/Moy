/*
    module  : neg.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef NEG_C
#define NEG_C

/**
neg  :  I  ->  J
Integer J is the negative of integer I.  Also supports float.
*/
PRIVATE void do_neg(void)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("neg");
    FLOAT("neg");
    if (stk->op == FLOAT_)
	stk->u.dbl = -stk->u.dbl;
    else
	stk->u.num = -stk->u.num;
}
#endif
