/*
    module  : drop.c
    version : 1.10
    date    : 03/05/24
*/
#ifndef DROP_C
#define DROP_C

/**
Q0  OK  2130  drop  :  DDA  A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
void drop_(pEnv env)
{
    int64_t i, j;
    Node aggr, elem, node;

    PARM(2, TAKE);
    env->stck = pvec_pop(env->stck, &elem);
    env->stck = pvec_pop(env->stck, &aggr);
    switch (aggr.op) {
    case LIST_:
	if ((j = pvec_cnt(aggr.u.lis)) <= elem.u.num)
	    node.u.lis = 0;
	else {
	    node.u.lis = pvec_init();
	    pvec_shallow_copy(node.u.lis, aggr.u.lis);
	    node.u.lis = pvec_cut(node.u.lis, j - elem.u.num);
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	if ((j = strlen(aggr.u.str)) <= elem.u.num)
	    node.u.str = "";
	else {
	    node.u.str = GC_malloc_atomic(j - elem.u.num + 1);
	    strcpy(node.u.str, aggr.u.str + elem.u.num);
	    node.op = STRING_;
	}
	break;

    case SET_:
	node.u.set = 0;
	for (j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		if (elem.u.num < 1)
		    node.u.set |= j;
		else
		    elem.u.num--;
	    }
	break;
    }
    node.op = aggr.op;
    env->stck = pvec_add(env->stck, node);
}
#endif
