/* ufloat.c */
PRIVATE void PROCEDURE()
{
    ONEPARAM(NAME);
    FLOAT(NAME);
    if (OUTSIDE)
	stk->u.dbl = FUNC(FLOATVAL);
    else
	UNARY(FLOAT_NEWNODE, FUNC(FLOATVAL));
}

#undef PROCEDURE
#undef NAME
#undef FUNC
