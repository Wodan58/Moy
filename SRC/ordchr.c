/*
    module  : ordchr.c
    version : 1.4
    date    : 03/12/17
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
	GNULLARY(RESULTTYP, stk->u.ptr);
}

#undef PROCEDURE
#undef NAME
#undef RESULTTYP
