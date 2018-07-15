/*
    module  : ordchr.h
    version : 1.9
    date    : 07/15/18
*/
PRIVATE void PROCEDURE(void)
{
#ifdef NEW_RUNTIME
    TRACE;
#else
#ifndef OLD_RUNTIME
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
#endif
}

#undef PROCEDURE
#undef NAME
#undef RESULTTYP
