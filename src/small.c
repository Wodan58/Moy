/*
    module  : small.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef SMALL_C
#define SMALL_C

/**
small  :  X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
PRIVATE void do_small(pEnv env)
{
    int i = 0, small = 0;

    ONEPARAM("small");
    switch (env->stk->op) {
    case BOOLEAN_:
    case INTEGER_:
	small = env->stk->u.num < 2;
	break;
    case SET_:
	if (!env->stk->u.set)
	    small = 1;
	else {
	    while (!(env->stk->u.set & ((long)1 << i)))
		i++;
	    small = (env->stk->u.set & ~((long)1 << i)) == 0;
	}
	break;
    case STRING_:
	small = !env->stk->u.str[0] || !env->stk->u.str[1];
	break;
    case LIST_:
	small = !env->stk->u.lis || !env->stk->u.lis->next;
	break;
    default:
	BADDATA("small");
	break;
    }
    UNARY(BOOLEAN_NEWNODE, small);
}
#endif
