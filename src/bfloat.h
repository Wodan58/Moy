/*
    module  : bfloat.h
    version : 1.9
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    FLOAT2(NAME);
    env->stk->next->u.dbl = FUNC(FLOATVAL2, FLOATVAL);
    env->stk->next->op = FLOAT_;
    POP(env->stk);
}

#undef PROCEDURE
#undef NAME
#undef FUNC
