/*
    module  : ufloat.h
    version : 1.9
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
    FLOAT(NAME);
    env->stk->u.dbl = FUNC(FLOATVAL);
}

#undef PROCEDURE
#undef NAME
#undef FUNC
