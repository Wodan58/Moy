/*
    module  : predsucc.h
    version : 1.8
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
    stk->u.num = stk->u.num OPER 1;
}

#undef PROCEDURE
#undef NAME
#undef OPER
