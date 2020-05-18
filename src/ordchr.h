/*
    module  : ordchr.h
    version : 1.10
    date    : 03/28/20
*/
PRIVATE void PROCEDURE(void)
{
#ifndef OLD_RUNTIME
    if (compiling && (INTEGER_1 || CHAR_1 || BOOLEAN_1))
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
    stk->op = RESULTTYP;
}

#undef PROCEDURE
#undef NAME
#undef RESULTTYP
