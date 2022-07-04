/*
    module  : drop.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef DROP_C
#define DROP_C

/**
drop  :  A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
PRIVATE void do_drop(pEnv env)
{
    char *str;
    int i, num;
    Node *node;
    long set;

    TWOPARAMS("drop");
    POSITIVEINDEX(env->stk, "drop");
    num = env->stk->u.num;
    POP(env->stk);
    switch (env->stk->op) {
    case LIST_:
	node = env->stk->u.lis;
	while (num-- > 0 && node)
	    node = node->next;
	UNARY(LIST_NEWNODE, node);
	break;
    case STRING_:
	str = env->stk->u.str;
	while (num-- > 0 && *str)
	    str++;
	UNARY(STRING_NEWNODE, GC_strdup(str));
	break;
    case SET_:
	for (set = i = 0; i < SETSIZE_; i++)
	    if (env->stk->u.set & ((long)1 << i)) {
		if (num < 1)
		    set |= (long)1 << i;
		else
		    num--;
	    }
	UNARY(SET_NEWNODE, set);
	break;
    default:
	BADAGGREGATE("drop");
	break;
    }
}
#endif
