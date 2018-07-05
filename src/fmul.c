/*
    module  : %M%
    version : %I%
    date    : %G%
*/
#ifdef RUNTIME
void do_fmul(void)
{
    float dbl1, dbl2;

    TRACE;
    memcpy(&dbl1, &stk[-2], sizeof(float));
    memcpy(&dbl2, &stk[-1], sizeof(float));
    dbl1 *= dbl2;
    memcpy(&stk[-2], &dbl1, sizeof(node_t));
    stk--;
}
#else
/**
.*  :  I J  ->  K
Integer K is the product of integers I and J.  Also supports float.
*/
PRIVATE void do_fmul(void)
{
#ifndef NCHECK
    if (compiling && FLOAT_1 && FLOAT_2)
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
