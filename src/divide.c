/*
    module  : divide.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef DIVIDE_C
#define DIVIDE_C

/**
/  :  I J  ->  K
Integer K is the (rounded) ratio of integers I and J.  Also supports float.
*/
PRIVATE void do_divide(void)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("/");
    FLOAT2("/");
#ifndef NCHECK
    if ((stk->op == FLOAT_ && !stk->u.dbl) ||
	(stk->op == INTEGER_ && !stk->u.num))
	execerror("non-zero divisor", "/");
#endif
    if (stk->next->op == FLOAT_)
	stk->next->u.dbl /= FLOATVAL;
    else if (stk->op == FLOAT_) {
	stk->next->u.dbl = stk->next->u.num / stk->u.dbl;
	stk->next->op = FLOAT_;
    } else
	stk->next->u.num /= stk->u.num;
    POP(stk);
}
#endif
