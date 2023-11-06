/*
    module  : step.c
    version : 1.9
    date    : 11/06/23
*/
#ifndef STEP_C
#define STEP_C

/**
OK 2770  step  :  DDU	A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
void step_(pEnv env)
{
    int64_t i, j;
    Node aggr, list, node;

    PARM(2, STEP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &aggr);
    switch (aggr.op) {
    case LIST_:
	for (i = 0, j = pvec_cnt(aggr.u.lis); i < j; i++) {
	    prog(env, list.u.lis);
	    prime(env, pvec_nth(aggr.u.lis, i));
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
	for (j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		prog(env, list.u.lis);
		node.u.num = i;
		prime(env, node);
	    }
	break;

    default:
	break;
    }
}
#endif
