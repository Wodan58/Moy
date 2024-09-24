/*
    module  : drop.c
    version : 1.11
    date    : 09/17/24
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
    Node elem, aggr, node;

    PARM(2, TAKE);
    elem = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
        j = vec_size(aggr.u.lis);
	if (elem.u.num > j)
	    elem.u.num = j;
        vec_shallow_copy(node.u.lis, aggr.u.lis);
        vec_setsize(node.u.lis, j - elem.u.num);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	j = strlen(aggr.u.str);
	if (elem.u.num >= j)
	    node.u.str = "";
	else {
	    node.u.str = GC_malloc_atomic(j - elem.u.num + 1);
	    strcpy(node.u.str, aggr.u.str + elem.u.num);
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
    vec_push(env->stck, node);
}
#endif
