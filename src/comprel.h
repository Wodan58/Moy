/*
    module  : comprel.h
    version : 1.12
    date    : 03/15/21
*/
#ifdef CASE_X
#undef CASE_X
#undef CASE_C
#endif

#include "case.c"

PRIVATE void PROCEDURE(pEnv env)
{
    double cmp;
    int i, j, error, comp = 0;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    if (env->stk->op == SET_) {
	i = env->stk->next->u.num;
	j = env->stk->u.num;
	comp = SETCMP;
    } else {
	cmp = Compare(env, env->stk->next, env->stk, &error);
	if (error)
	    BADDATA(NAME);
	else
	    comp = cmp OPR 0;
    }
    env->stk->next->op = CONSTRUCTOR;
    env->stk->next->u.num = comp;
    POP(env->stk);
}

#undef PROCEDURE
#undef NAME
#undef CONSTRUCTOR
#undef OPR
#undef SETCMP
