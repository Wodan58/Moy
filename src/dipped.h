/*
    module  : dipped.h
    version : 1.10
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
    Node temp;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    PARAMCOUNT(NAME);
    temp = *env->stk;
    POP(env->stk);
    ARGUMENT(env);
    DUPLICATE(&temp);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef ARGUMENT
