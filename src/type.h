/*
    module  : type.h
    version : 1.9
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
    env->stk->u.num = env->stk->op REL TYP;
    env->stk->op = BOOLEAN_;
}

#undef PROCEDURE
#undef NAME
#undef REL
#undef TYP
