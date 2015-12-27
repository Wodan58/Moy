/* ldexp.c */
PRIVATE void ldexp_()
{
    int exp;

    TWOPARAMS("ldexp");
    INTEGER("ldexp");
    exp = stk->u.num;
    POP(stk);
    FLOAT("ldexp");
    if (OUTSIDE)
	stk->u.dbl = ldexp(FLOATVAL, exp);
    else
	UNARY(FLOAT_NEWNODE, ldexp(FLOATVAL, exp));
}
