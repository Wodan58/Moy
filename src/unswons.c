/*
    module  : unswons.c
    version : 1.12
    date    : 06/20/22
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
    long set;

    ONEPARAM("unswons");
    switch (env->stk->op) {
    case LIST_:
	save = env->stk->u.lis;
	CHECKEMPTYLIST(save, "unswons");
	UNARY(LIST_NEWNODE, save->next);
	DUPLICATE(save);
	break;
    case STRING_:
	str = env->stk->u.str;
	CHECKEMPTYSTRING(str, "unswons");
	UNARY(STRING_NEWNODE, GC_strdup(str + 1));
	PUSH_NUM(CHAR_, *str);
	break;
    case SET_:
	set = env->stk->u.set;
	CHECKEMPTYSET(set, "unswons");
	while (!(set & ((long)1 << i)))
	    i++;
	UNARY(SET_NEWNODE, set & ~((long)1 << i));
	PUSH_NUM(INTEGER_, i);
	break;
    default:
	BADAGGREGATE("unswons");
	break;
    }
}
#endif
