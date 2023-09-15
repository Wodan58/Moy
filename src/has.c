/*
    module  : has.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef HAS_C
#define HAS_C

#include "compare.h"

/**
OK 2290  has  :  DDA	A X  ->  B
Tests whether aggregate A has X as a member.
*/
void has_(pEnv env)
{
    int i, found = 0;
    Node aggr, elem, node;

    PARM(2, HAS);
    elem = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	for (i = lst_size(aggr.u.lis) - 1; i >= 0; i--) {
	    node = lst_at(aggr.u.lis, i);
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
    default:
	break;
    }
    node.u.num = found;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
