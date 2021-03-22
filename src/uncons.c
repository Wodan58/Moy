/*
    module  : uncons.c
    version : 1.16
    date    : 03/15/21
*/
#ifndef UNCONS_C
#define UNCONS_C

/**
uncons  :  A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
PRIVATE void do_uncons(pEnv env)
{
    char *str;
    int i = 0;
    Node *save;
    ulong_t set;

#ifndef OLD_RUNTIME
    if (compiling && env->stk && ((env->stk->op == LIST_ && env->stk->u.lis->op > USR_ &&
	env->stk->u.lis->op <= SYMBOL_) || env->stk->op == STRING_ || env->stk->op == SET_))
	;
    else
	COMPILE;
#endif
    ONEPARAM("uncons");
    switch (env->stk->op) {
    case LIST_:
	CHECKEMPTYLIST(env->stk->u.lis, "uncons");
	save = env->stk->u.lis;
	env->stk->op = env->stk->u.lis->op;
	env->stk->u = env->stk->u.lis->u;
	PUSH_PTR(LIST_, save->next);
	break;
    case STRING_:
	str = env->stk->u.str;
	CHECKEMPTYSTRING(str, "uncons");
	env->stk->u.num = *str;
	env->stk->op = CHAR_;
	PUSH_PTR(STRING_, GC_strdup(++str));
	break;
    case SET_:
	set = env->stk->u.set;
	CHECKEMPTYSET(set, "uncons");
	while (!(set & ((long_t)1 << i)))
	    i++;
	env->stk->u.num = i;
	env->stk->op = INTEGER_;
	PUSH_NUM(SET_, set & ~((long_t)1 << i));
	break;
    default:
	BADAGGREGATE("uncons");
	break;
    }
}
#endif
