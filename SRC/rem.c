/* rem.c */
PRIVATE void rem_()
{
    TWOPARAMS("rem");
    FLOAT2("rem");
    if ((stk->op == FLOAT_ && stk->u.dbl == 0.0) ||
	(stk->op == INTEGER_ && stk->u.num == 0))
	execerror("non-zero operand", "rem");
    if (OUTSIDE) {
	if (stk->next->op == FLOAT_)
	    stk->next->u.dbl = fmod(stk->next->u.dbl, FLOATVAL);
	else if (stk->op == FLOAT_) {
	    stk->next->u.dbl = fmod((double) stk->next->u.num, stk->u.dbl);
	    stk->next->op = FLOAT_;
	} else
	    stk->next->u.num %= stk->u.num;
	POP(stk);
    } else if (stk->op == FLOAT_ || stk->next->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, fmod(FLOATVAL2, FLOATVAL));
    else
	BINARY(INTEGER_NEWNODE, stk->next->u.num % stk->u.num);
}
