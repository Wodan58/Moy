/*
    module  : at.c
    version : 1.7
    date    : 09/15/23
*/
#ifndef AT_C
#define AT_C

/**
OK 2060  at  :  DDA	A I  ->  X
X (= A[I]) is the member of A at position I.
*/
void at_(pEnv env)
{
    int i, j;
    Node elem, aggr, node;

    PARM(2, AT);
    elem = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	node = lst_at(aggr.u.lis, lst_size(aggr.u.lis) - elem.u.num - 1);
	lst_push(env->stck, node);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.u.num = aggr.u.str[elem.u.num];
	node.op = CHAR_;
	lst_push(env->stck, node);
	break;

    case SET_:
	for (j = elem.u.num, i = 0; i < SETSIZE; i++)
	    if (aggr.u.set & ((int64_t)1 << i)) {
		if (!j) {
		    node.u.num = i;
		    node.op = INTEGER_;
		    lst_push(env->stck, node);
		    break;
		}
		j--;
	    }
	break;

    default:
	break;
    }
}
#endif
