/*
    module  : divide.c
    version : 1.6
    date    : 07/02/18
*/

/**
/  :  I J  ->  K
Integer K is the (rounded) ratio of integers I and J.  Also supports float.
*/
PRIVATE void do_divide(void)
{
#ifndef NCHECK
    if (compiling && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("/");
    FLOAT2("/");
    if ((stk->op == FLOAT_ && !stk->u.dbl) ||
	(stk->op == INTEGER_ && !stk->u.num))
	execerror("non-zero divisor", "/");
    if (OUTSIDE) {
	if (stk->next->op == FLOAT_)
	    stk->next->u.dbl /= FLOATVAL;
	else if (stk->op == FLOAT_) {
	    stk->next->u.dbl = stk->next->u.num / stk->u.dbl;
	    stk->next->op = FLOAT_;
	} else
	    stk->next->u.num /= stk->u.num;
	POP(stk);
    } else if (stk->op == FLOAT_ || stk->next->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, (FLOATVAL2) / (FLOATVAL));
    else
	BINARY(INTEGER_NEWNODE, stk->next->u.num / stk->u.num);
}
