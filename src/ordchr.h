/*
    module  : ordchr.h
    version : 1.8
    date    : 07/10/18
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (compiling && (INTEGER_1 || CHAR_1 || BOOLEAN_1))
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
    if (OUTSIDE)
	stk->op = RESULTTYP;
    else
	GUNARY(RESULTTYP, stk->u.ptr);
}

#undef PROCEDURE
#undef NAME
#undef RESULTTYP
