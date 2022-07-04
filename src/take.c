/*
    module  : take.c
    version : 1.15
    date    : 06/20/22
*/
#ifndef TAKE_C
#define TAKE_C

/**
take  :  A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
PRIVATE void do_take(pEnv env)
{
    int i, num;
    long set;
    char *str = "";
    Node *root = 0, *cur, *last;

    TWOPARAMS("take");
    POSITIVEINDEX(env->stk, "take");
    num = env->stk->u.num;
    POP(env->stk);
    switch (env->stk->op) {
    case LIST_:
	if (num >= 1) {
	    for (cur = env->stk->u.lis; cur && num-- > 0; cur = cur->next)
		if (!root)
		    last = root = newnode(cur->op, cur->u, 0);
		else
		    last = last->next = newnode(cur->op, cur->u, 0);
	}
	UNARY(LIST_NEWNODE, root);
	break;
    case STRING_:
	if (num >= 1) {
	    str = GC_malloc_atomic(num + 1);
	    strncpy(str, env->stk->u.str, num);
	    str[num] = 0;
	}
	UNARY(STRING_NEWNODE, str);
	break;
    case SET_:
	for (set = i = 0; i < SETSIZE_; i++)
	    if (env->stk->u.set & ((long)1 << i)) {
		if (num-- > 0)
		    set |= (long)1 << i;
		else
		    break;
	    }
	UNARY(SET_NEWNODE, set);
	break;
    default:
	BADAGGREGATE("take");
	break;
    }
}
#endif
