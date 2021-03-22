/*
    module  : concat.c
    version : 1.15
    date    : 03/15/21
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

#ifndef OLD_RUNTIME
    if (compiling && VALID_2 && AGGREGATE_1 && AGGREGATE_2 &&
	env->stk->op == env->stk->next->op)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("concat");
    SAME2TYPES("concat");
    switch (env->stk->op) {
    case LIST_:
	if (!env->stk->next->u.lis) {
	    env->stk->next->u.lis = env->stk->u.lis;
	    POP(env->stk);
	    return;
	}
	for (cur = env->stk->next->u.lis; cur; cur = cur->next)
	    if (!root)
		last = root = newnode(cur->op, cur->u, 0);
	    else
		last = last->next = newnode(cur->op, cur->u, 0);
	last->next = env->stk->u.lis;
	env->stk->next->u.lis = root;
	POP(env->stk);
	break;
    case STRING_:
	i = strlen(env->stk->next->u.str);
	str = GC_malloc_atomic(i + strlen(env->stk->u.str) + 1);
	strcpy(str, env->stk->next->u.str);
	strcpy(str + i, env->stk->u.str);
	env->stk->next->u.str = str;
	POP(env->stk);
	break;
    case SET_:
	env->stk->next->u.set |= env->stk->u.set;
	POP(env->stk);
	break;
    default:
	BADAGGREGATE("concat");
	break;
    }
}
#endif
