/* trunc.c */
PRIVATE void trunc_()
{
    ONEPARAM("trunc");
    FLOAT("trunc");
    if (OUTSIDE) {
	stk->u.num = FLOATVAL;
	stk->op = INTEGER_;
    } else
	UNARY(INTEGER_NEWNODE, (long_t) FLOATVAL);
}
