/*
    module  : drop.c
    version : 1.11
    date    : 03/15/21
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
    ulong_t set;

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1 && AGGREGATE_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("drop");
    num = env->stk->u.num;
    POP(env->stk);
    switch (env->stk->op) {
    case LIST_:
	node = env->stk->u.lis;
	while (num-- > 0 && node)
	    node = node->next;
	env->stk->u.lis = node;
	break;
    case STRING_:
	str = env->stk->u.str;
	while (num-- > 0 && *str)
	    str++;
	env->stk->u.str = GC_strdup(str);
	break;
    case SET_:
	for (set = i = 0; i < SETSIZE_; i++)
	    if (env->stk->u.set & ((long_t)1 << i)) {
		if (num < 1)
		    set |= (long_t)1 << i;
		else
		    num--;
	    }
	env->stk->u.set = set;
	break;
    default:
	BADAGGREGATE("drop");
	break;
    }
}
#endif
