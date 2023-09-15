/*
    module  : swons.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef SWONS_C
#define SWONS_C

/**
OK 2020  swons  :  DDA	A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void swons_(pEnv env)
{
    Node elem, aggr, node;

    PARM(2, HAS);
    elem = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	lst_init(node.u.lis);
	if (lst_size(aggr.u.lis))
	    lst_shallow_copy_take_ownership(node.u.lis, aggr.u.lis);
	lst_push(node.u.lis, elem);
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
    lst_push(env->stck, node);
}
#endif
