/*
    module  : ordchr.c
    version : 1.5
    date    : 03/18/17
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (optimizing && (INTEGER_1 || CHAR_1 || BOOLEAN_1))
	;
    else
	COMPILE;
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
#endif
    if (OUTSIDE)
	stk->op = RESULTTYP;
    else
	GUNARY(RESULTTYP, stk->u.ptr);
}

#undef PROCEDURE
#undef NAME
#undef RESULTTYP
