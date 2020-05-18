/*
    module  : ufloat.h
    version : 1.8
    date    : 03/28/20
*/
PRIVATE void PROCEDURE(void)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
    FLOAT(NAME);
    stk->u.dbl = FUNC(FLOATVAL);
}

#undef PROCEDURE
#undef NAME
#undef FUNC
