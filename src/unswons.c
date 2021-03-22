/*
    module  : unswons.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef UNSWONS_C
#define UNSWONS_C

/**
unswons  :  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
PRIVATE void do_unswons(pEnv env)
{
    char *str;
    int i = 0;
    Node *save;
    ulong_t set;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("unswons");
    switch (env->stk->op) {
    case LIST_:
	CHECKEMPTYLIST(env->stk->u.lis, "unswons");
	save = env->stk->u.lis;
	env->stk->u.lis = env->stk->u.lis->next;
	DUPLICATE(save);
	break;
    case STRING_:
	str = env->stk->u.str;
	CHECKEMPTYSTRING(str, "unswons");
	env->stk->u.str = GC_strdup(str + 1);
	PUSH_NUM(CHAR_, *str);
	break;
    case SET_:
	set = env->stk->u.set;
	CHECKEMPTYSET(set, "unswons");
	while (!(set & ((long_t)1 << i)))
	    i++;
	env->stk->u.set = set & ~((long_t)1 << i);
	PUSH_NUM(INTEGER_, i);
	break;
    default:
	BADAGGREGATE("unswons");
	break;
    }
}
#endif
