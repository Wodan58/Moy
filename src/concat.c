/*
    module  : concat.c
    version : 1.16
    date    : 06/20/22
*/
#ifndef CONCAT_C
#define CONCAT_C

/**
concat  :  S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
PRIVATE void do_concat(pEnv env)
{
    char *str;
    unsigned i;
    Node *cur = 0, *root = 0, *last = 0;

    TWOPARAMS("concat");
    SAME2TYPES("concat");
    switch (env->stk->op) {
    case LIST_:
	if (!env->stk->next->u.lis) {
	    BINARY(LIST_NEWNODE, env->stk->u.lis);
	    return;
	}
	for (cur = env->stk->next->u.lis; cur; cur = cur->next)
	    if (!root)
		last = root = newnode(cur->op, cur->u, 0);
	    else
		last = last->next = newnode(cur->op, cur->u, 0);
	last->next = env->stk->u.lis;
	BINARY(LIST_NEWNODE, root);
	break;
    case STRING_:
	i = strlen(env->stk->next->u.str);
	str = GC_malloc_atomic(i + strlen(env->stk->u.str) + 1);
	strcpy(str, env->stk->next->u.str);
	strcpy(str + i, env->stk->u.str);
	BINARY(STRING_NEWNODE, str);
	break;
    case SET_:
	BINARY(SET_NEWNODE, env->stk->next->u.set | env->stk->u.set);
	break;
    default:
	BADAGGREGATE("concat");
	break;
    }
}
#endif
