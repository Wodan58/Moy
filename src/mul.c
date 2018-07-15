/*
    module  : mul.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef MUL_X
#define MUL_C

#ifdef NEW_RUNTIME
void do_mul(void)
{
    TRACE;
    stk[-2] *= stk[-1];
    (void)do_pop();
}
#else
/**
*  :  I J  ->  K
Integer K is the product of integers I and J.  Also supports float.
*/
PRIVATE void do_mul(void)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("*");
    FLOAT2("*");
    if (OUTSIDE) {
	if (stk->next->op == FLOAT_)
	    stk->next->u.dbl *= FLOATVAL;
	else if (stk->op == FLOAT_) {
	    stk->next->u.dbl = stk->next->u.num * stk->u.dbl;
	    stk->next->op = FLOAT_;
	} else
	    stk->next->u.num *= stk->u.num;
	POP(stk);
    } else if (stk->op == FLOAT_ || stk->next->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, (FLOATVAL2) * (FLOATVAL));
    else
	BINARY(INTEGER_NEWNODE, stk->next->u.num * stk->u.num);
}
#endif
#endif
