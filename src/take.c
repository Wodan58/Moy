/*
    module  : take.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef TAKE_C
#define TAKE_C

/**
Q0  OK  2140  take  :  DDA  A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
void take_(pEnv env)
{
    int64_t i, j;
    Node elem, aggr, node;

    PARM(2, TAKE);
    env->stck = pvec_pop(env->stck, &elem);
    env->stck = pvec_pop(env->stck, &aggr);
    node = aggr;
    switch (aggr.op) {
    case LIST_:
	if ((j = pvec_cnt(aggr.u.lis)) <= elem.u.num)
	    node = aggr;
	else {
	    node.u.lis = pvec_init();
	    for (i = j - elem.u.num; i < j; i++)
		node.u.lis = pvec_add(node.u.lis, pvec_nth(aggr.u.lis, i));
	    node.op = LIST_;
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	if ((j = strlen(aggr.u.str)) <= elem.u.num)
	    node = aggr;
	else {
	    node.u.str = GC_malloc_atomic(elem.u.num + 1);
	    strncpy(node.u.str, aggr.u.str, elem.u.num);
	    node.u.str[elem.u.num] = 0;
	    node.op = STRING_;
	}
	break;

    case SET_:
	node.u.set = 0;
	for (j = 1, i = 0; i < SETSIZE && elem.u.num; i++, j <<= 1)
	    if (aggr.u.set & j) {
		node.u.set |= j;
		elem.u.num--;
	    }
	node.op = SET_;
	break;
    }
    env->stck = pvec_add(env->stck, node);
}
#endif
