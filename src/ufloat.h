/*
    module  : ufloat.h
    version : 1.3
    date    : 03/12/17
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (optimizing && NUMERIC_1)
	;
    else
	COMPILE;
    ONEPARAM(NAME);
    FLOAT(NAME);
#endif
    if (OUTSIDE)
	stk->u.dbl = FUNC(FLOATVAL);
    else
	UNARY(FLOAT_NEWNODE, FUNC(FLOATVAL));
}

#undef PROCEDURE
#undef NAME
#undef FUNC
