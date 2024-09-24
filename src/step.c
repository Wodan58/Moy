/*
    module  : step.c
    version : 1.14
    date    : 09/17/24
*/
#ifndef STEP_C
#define STEP_C

/**
Q1  OK  2770  step  :  DDQ  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
void step_(pEnv env)
{
    int i, j;
    Node list, aggr, node;

    PARM(2, STEP);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	for (i = 0, j = vec_size(aggr.u.lis); i < j; i++) {
	    prog(env, list.u.lis);
	    prime(env, vec_at(aggr.u.lis, i));
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.op = CHAR_;
	for (i = strlen(aggr.u.str) - 1; i >= 0; i--) {
	    prog(env, list.u.lis);
	    node.u.num = aggr.u.str[i];
	    prime(env, node);
	}
	break;

    case SET_:
	node.op = INTEGER_;
	for (i = SETSIZE - 1; i >= 0; i--)
	    if (aggr.u.set & ((int64_t)1 << i)) {
		prog(env, list.u.lis);
		node.u.num = i;
		prime(env, node);
	    }
	break;
    }
}
#endif
