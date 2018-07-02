/*
    module  : ufloat.h
    version : 1.4
    date    : 07/02/18
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
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
