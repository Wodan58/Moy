/*
    module  : rest.c
    version : 1.11
    date    : 06/20/22
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

    ONEPARAM("rest");
    switch (env->stk->op) {
    case LIST_:
	CHECKEMPTYLIST(env->stk->u.lis, "rest");
	UNARY(LIST_NEWNODE, env->stk->u.lis->next);
	break;
    case STRING_:
	str = env->stk->u.str;
	CHECKEMPTYSTRING(str, "rest");
	UNARY(STRING_NEWNODE, GC_strdup(++str));
	break;
    case SET_:
	CHECKEMPTYSET(env->stk->u.set, "rest");
	while (!(env->stk->u.set & ((long)1 << i)))
	    i++;
	UNARY(SET_NEWNODE, env->stk->u.set & ~((long)1 << i));
	break;
    default:
	BADAGGREGATE("rest");
	break;
    }
}
#endif
