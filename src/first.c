/*
    module  : first.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef FIRST_C
#define FIRST_C

/**
first  :  A  ->  F
F is the first member of the non-empty aggregate A.
*/
PRIVATE void do_first(pEnv env)
{
    int i = 0;

#ifndef OLD_RUNTIME
    if (compiling && AGGREGATE_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("first");
    switch (env->stk->op) {
    case LIST_:
	CHECKEMPTYLIST(env->stk->u.lis, "first");
	env->stk->op = env->stk->u.lis->op;
	env->stk->u = env->stk->u.lis->u;
	break;
    case STRING_:
	CHECKEMPTYSTRING(env->stk->u.str, "first");
	env->stk->u.num = *env->stk->u.str;
	env->stk->op = CHAR_;
	break;
    case SET_:
	CHECKEMPTYSET(env->stk->u.set, "first");
	while (!(env->stk->u.set & ((long_t)1 << i)))
	    i++;
	env->stk->u.num = i;
	env->stk->op = INTEGER_;
	break;
    default:
	BADAGGREGATE("first");
	break;
    }
}
#endif
