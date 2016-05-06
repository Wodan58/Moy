/*
    module  : ufloat.c
    version : 1.2
    date    : 05/06/16
*/
/* ufloat.c */
PRIVATE void PROCEDURE(void)
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
