/*
    module  : first.c
    version : 1.13
    date    : 06/20/22
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

    ONEPARAM("first");
    switch (env->stk->op) {
    case LIST_:
	CHECKEMPTYLIST(env->stk->u.lis, "first");
	GUNARY(env->stk->u.lis->op, env->stk->u.lis->u);
	break;
    case STRING_:
	CHECKEMPTYSTRING(env->stk->u.str, "first");
	UNARY(CHAR_NEWNODE, *env->stk->u.str);
	break;
    case SET_:
	CHECKEMPTYSET(env->stk->u.set, "first");
	while (!(env->stk->u.set & ((long)1 << i)))
	    i++;
	UNARY(INTEGER_NEWNODE, i);
	break;
    default:
	BADAGGREGATE("first");
	break;
    }
}
#endif
