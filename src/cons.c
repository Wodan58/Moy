/*
    module  : cons.c
    version : 1.8
    date    : 10/02/23
*/
#ifndef CONS_C
#define CONS_C

/**
OK 2010  cons  :  DDA	X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void cons_(pEnv env)
{
    Node elem, aggr, node;

    PARM(2, CONS);
    env->stck = pvec_pop(env->stck, &aggr);
    env->stck = pvec_pop(env->stck, &elem);
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

    default:
	node = aggr;
	break;
    }
    node.op = aggr.op;
    env->stck = pvec_add(env->stck, node);
}
#endif
