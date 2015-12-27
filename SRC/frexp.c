/* frexp.c */
PRIVATE void frexp_()
{
    int exp;

    ONEPARAM("frexp");
    FLOAT("frexp");
    if (OUTSIDE)
	stk->u.dbl = frexp(FLOATVAL, &exp);
    else
	UNARY(FLOAT_NEWNODE, frexp(FLOATVAL, &exp));
    PUSH(INTEGER_, exp);
}
