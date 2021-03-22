/*
    module  : rest.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef REST_C
#define REST_C

/**
rest  :  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
PRIVATE void do_rest(pEnv env)
{
    int i = 0;
    char *str;

#ifndef OLD_RUNTIME
    if (compiling && AGGREGATE_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("rest");
    switch (env->stk->op) {
    case LIST_:
	CHECKEMPTYLIST(env->stk->u.lis, "rest");
	env->stk->u.lis = env->stk->u.lis->next;
	break;
    case STRING_:
	str = env->stk->u.str;
	CHECKEMPTYSTRING(str, "rest");
	env->stk->u.str = GC_strdup(++str);
	break;
    case SET_:
	CHECKEMPTYSET(env->stk->u.set, "rest");
	while (!(env->stk->u.set & ((long_t)1 << i)))
	    i++;
	env->stk->u.set = env->stk->u.set & ~((long_t)1 << i);
	break;
    default:
	BADAGGREGATE("rest");
	break;
    }
}
#endif
