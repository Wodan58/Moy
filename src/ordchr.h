/*
    module  : ordchr.h
    version : 1.11
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && (INTEGER_1 || CHAR_1 || BOOLEAN_1))
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
    env->stk->op = RESULTTYP;
}

#undef PROCEDURE
#undef NAME
#undef RESULTTYP
