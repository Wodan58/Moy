/*
    module  : not.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef NOT_C
#define NOT_C

/**
not  :  X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
PRIVATE void do_not(pEnv env)
{
    int num = 0;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("not");
    switch (env->stk->op) {
    case SET_:
	env->stk->u.set = ~env->stk->u.set;
	return;
    case BOOLEAN_:
	num = !env->stk->u.num;
	break;
    default:
	BADDATA("not");
	break;
    }
    env->stk->u.num = num;
    env->stk->op = BOOLEAN_;
}
#endif
