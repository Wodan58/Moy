/*
    module  : take.c
    version : 1.10
    date    : 09/17/24
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
    elem = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    node = aggr;
    switch (aggr.op) {
    case LIST_:
        if ((j = vec_size(aggr.u.lis)) > elem.u.num) {
            vec_init(node.u.lis);
            for (i = j - elem.u.num; i < j; i++)
                vec_push(node.u.lis, vec_at(aggr.u.lis, i));
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	if ((j = strlen(aggr.u.str)) > elem.u.num) {
	    node.u.str = GC_malloc_atomic(elem.u.num + 1);
	    strncpy(node.u.str, aggr.u.str, elem.u.num);
	    node.u.str[elem.u.num] = 0;
	}
	break;

    case SET_:
	node.u.set = 0;
	for (j = 1, i = 0; i < SETSIZE && elem.u.num; i++, j <<= 1)
	    if (aggr.u.set & j) {
		node.u.set |= j;
		elem.u.num--;
	    }
	break;
    }
    vec_push(env->stck, node);
}
#endif
