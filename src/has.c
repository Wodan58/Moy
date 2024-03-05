/*
    module  : has.c
    version : 1.10
    date    : 03/05/24
*/
#ifndef HAS_C
#define HAS_C

#include "compare.h"

/**
Q0  OK  2290  has  :  DDA  A X  ->  B
Tests whether aggregate A has X as a member.
*/
void has_(pEnv env)
{
    int i, found = 0;
    Node aggr, elem, node;

    PARM(2, HAS);
    env->stck = pvec_pop(env->stck, &elem);
    env->stck = pvec_pop(env->stck, &aggr);
    switch (aggr.op) {
    case LIST_:
	for (i = pvec_cnt(aggr.u.lis) - 1; i >= 0; i--) {
	    node = pvec_nth(aggr.u.lis, i);
	    if (!Compare(env, node, elem)) {
		found = 1;
		break;
	    }
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	for (i = strlen(aggr.u.str) - 1; i >= 0; i--)
	    if (aggr.u.str[i] == elem.u.num) {
		found = 1;
		break;
	    }
	break;

    case SET_:
	found = (aggr.u.set & ((int64_t)1 << elem.u.num)) > 0;
	break;
    }
    node.u.num = found;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
