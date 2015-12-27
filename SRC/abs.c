/* abs.c */
PRIVATE void abs_()
{
    ONEPARAM("abs");
    FLOAT("abs");
    if (OUTSIDE) {
	if (stk->op == FLOAT_)
	    stk->u.dbl = fabs(stk->u.dbl);
	else if (stk->u.num < 0)
	    stk->u.num = -stk->u.num;
    } else if (stk->op == FLOAT_)
	UNARY(FLOAT_NEWNODE, fabs(stk->u.dbl));
    else if (stk->u.num < 0)
	UNARY(INTEGER_NEWNODE, -stk->u.num);
}
