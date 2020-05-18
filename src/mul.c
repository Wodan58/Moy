/*
    module  : mul.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef MUL_C
#define MUL_C

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
    if (stk->next->op == FLOAT_)
	stk->next->u.dbl *= FLOATVAL;
    else if (stk->op == FLOAT_) {
	stk->next->u.dbl = stk->next->u.num * stk->u.dbl;
	stk->next->op = FLOAT_;
    } else
	stk->next->u.num *= stk->u.num;
    POP(stk);
}
#endif
