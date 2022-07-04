/*
    module  : comprel.h
    version : 1.13
    date    : 06/20/22
*/
#include "compare.h"

PRIVATE void PROCEDURE(pEnv env)
{
    long i, j;
    int comp = 0;

    TWOPARAMS(NAME);
    if (env->stk->op == SET_) {
	i = env->stk->next->u.num;
	j = env->stk->u.num;
	comp = SETCMP;
    } else
	comp = Compare(env, env->stk->next, env->stk) OPR 0;
    BINARY(CONSTRUCTOR, comp);
}

#undef PROCEDURE
#undef NAME
#undef CONSTRUCTOR
#undef OPR
#undef SETCMP
