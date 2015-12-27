/* modf.c */
PRIVATE void modf_()
{
    double exp;

    ONEPARAM("modf");
    FLOAT("modf");
    if (OUTSIDE)
	stk->u.dbl = modf(FLOATVAL, &exp);
    else
	UNARY(FLOAT_NEWNODE, modf(FLOATVAL, &exp));
    PUSH(FLOAT_, exp);
}
