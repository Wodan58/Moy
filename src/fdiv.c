/*
    module  : fdiv.c
    version : 1.3
    date    : 07/15/18
*/
#ifndef FDIV_X
#define FDIV_C

#ifdef NEW_RUNTIME
void do_fdiv(void)
{
    float dbl1, dbl2;

    TRACE;
    memcpy(&dbl1, &stk[-2], sizeof(float));
    memcpy(&dbl2, &stk[-1], sizeof(float));
    dbl1 /= dbl2;
    memcpy(&stk[-2], &dbl1, sizeof(node_t));
    (void)do_pop();
}
#else
/**
./  :  I J  ->  K
Integer K is the (rounded) ratio of integers I and J.  Also supports float.
*/
PRIVATE void do_fdiv(void)
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
#endif
#endif
