/*
    module  : neg.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef NEG_X
#define NEG_C

#ifdef NEW_RUNTIME
void do_neg(void)
{
    TRACE;
    stk[-1] = -stk[-1];
}
#else
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
    if (OUTSIDE) {
	if (stk->op == FLOAT_)
	    stk->u.dbl = -stk->u.dbl;
	else
	    stk->u.num = -stk->u.num;
    } else if (stk->op == FLOAT_)
	UNARY(FLOAT_NEWNODE, -stk->u.dbl);
    else if (stk->u.num)
	UNARY(INTEGER_NEWNODE, -stk->u.num);
}
#endif
#endif
