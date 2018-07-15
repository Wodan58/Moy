/*
    module  : ufloat.h
    version : 1.7
    date    : 07/15/18
*/
PRIVATE void PROCEDURE(void)
{
#ifdef NEW_RUNTIME
    float dbl;

    TRACE;
    memcpy(&dbl, &stk[-1], sizeof(float));
    dbl = FUNC(dbl);
    memcpy(&stk[-1], &dbl, sizeof(node_t));
#else
#ifndef OLD_RUNTIME
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
#endif
}

#undef PROCEDURE
#undef NAME
#undef FUNC
