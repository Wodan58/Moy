/*
    module  : small.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef SMALL_C
#define SMALL_C

/**
small  :  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
PRIVATE void do_small(pEnv env)
{
    int small = 0;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("small");
    switch (env->stk->op) {
    case BOOLEAN_:
    case INTEGER_:
	small = env->stk->u.num < 2;
	break;
    case SET_:
	if (!env->stk->u.set)
	    small = 1;
	else {
	    int i = 0;
	    while (!(env->stk->u.set & ((long_t)1 << i)))
		i++;
	    small = (env->stk->u.set & ~((long_t)1 << i)) == 0;
	}
	break;
    case STRING_:
	small = !env->stk->u.str[0] || !env->stk->u.str[1];
	break;
    case LIST_:
	small = !env->stk->u.lis || !env->stk->u.lis->next;
	break;
    default:
	BADDATA("small");
	break;
    }
    env->stk->u.num = small;
    env->stk->op = BOOLEAN_;
}
#endif
