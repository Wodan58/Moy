/*
    module  : drop.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef DROP_C
#define DROP_C

/**
OK 2130  drop  :  DDA	A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
void drop_(pEnv env)
{
    int i, j;
    Node aggr, elem, node;

    PARM(2, TAKE);
    elem = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	j = lst_size(aggr.u.lis);
	if (elem.u.num >= j)
	    node.u.lis = 0;
	else {
	    lst_init(node.u.lis);
	    lst_shallow_copy(node.u.lis, aggr.u.lis);
	    lst_resize(node.u.lis, j - elem.u.num);
	}
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
	    node.op = STRING_;
	}
	break;

    case SET_:
	node.u.set = 0;
	for (i = 0, j = elem.u.num; i < SETSIZE; i++)
	    if (aggr.u.set & ((int64_t)1 << i)) {
		if (j < 1)
		    node.u.set |= ((int64_t)1 << i);
		else
		    j--;
	    }
	break;

    default:
	node = aggr;
	break;
    }
    node.op = aggr.op;
    lst_push(env->stck, node);
}
#endif
