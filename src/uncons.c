/*
    module  : uncons.c
    version : 1.17
    date    : 06/20/22
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
    long set;

    ONEPARAM("uncons");
    switch (env->stk->op) {
    case LIST_:
	save = env->stk->u.lis;
	CHECKEMPTYLIST(save, "uncons");
	GUNARY(save->op, save->u);
	PUSH_PTR(LIST_, save->next);
	break;
    case STRING_:
	str = env->stk->u.str;
	CHECKEMPTYSTRING(str, "uncons");
	UNARY(CHAR_NEWNODE, *str);
	PUSH_PTR(STRING_, GC_strdup(++str));
	break;
    case SET_:
	set = env->stk->u.set;
	CHECKEMPTYSET(set, "uncons");
	while (!(set & ((long)1 << i)))
	    i++;
	UNARY(INTEGER_NEWNODE, i);
	PUSH_NUM(SET_, set & ~((long)1 << i));
	break;
    default:
	BADAGGREGATE("uncons");
	break;
    }
}
#endif
