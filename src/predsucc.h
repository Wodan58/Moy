/*
    module  : predsucc.h
    version : 1.9
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
    env->stk->u.num = env->stk->u.num OPER 1;
}

#undef PROCEDURE
#undef NAME
#undef OPER
