/*
    module  : swons.c
    version : 1.10
    date    : 03/05/24
*/
#ifndef SWONS_C
#define SWONS_C

/**
Q0  OK  2020  swons  :  DDA  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void swons_(pEnv env)
{
    Node elem, aggr, node;

    PARM(2, HAS);
    env->stck = pvec_pop(env->stck, &elem);
    env->stck = pvec_pop(env->stck, &aggr);
    switch (aggr.op) {
    case LIST_:
	node.u.lis = pvec_init();
	if (pvec_cnt(aggr.u.lis))
	    pvec_shallow_copy_take_ownership(node.u.lis, aggr.u.lis);
	node.u.lis = pvec_add(node.u.lis, elem);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.u.str = GC_malloc_atomic(strlen(aggr.u.str) + 2);
	node.u.str[0] = elem.u.num;
	strcpy(&node.u.str[1], aggr.u.str);
	break;

    case SET_:
	node.u.set = aggr.u.set | ((int64_t)1 << elem.u.num);
	break;
    }
    node.op = aggr.op;
    env->stck = pvec_add(env->stck, node);
}
#endif
