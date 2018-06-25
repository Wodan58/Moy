/*
    module  : ordchr.h
    version : 1.6
    date    : 04/09/17
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (optimizing)
	chg_history(RESULTTYP);
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
