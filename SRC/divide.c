/* divide.c */
PRIVATE void divide_()
{
    TWOPARAMS("/");
    FLOAT2("/");
    if ((stk->op == FLOAT_ && stk->u.dbl == 0.0) ||
	(stk->op == INTEGER_ && stk->u.num == 0))
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
