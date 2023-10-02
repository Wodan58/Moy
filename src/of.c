/*
    module  : of.c
    version : 1.8
    date    : 10/02/23
*/
#ifndef OF_C
#define OF_C

/**
OK 2070  of  :  DDA	I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
void of_(pEnv env)
{
    int64_t i, j;
    Node elem, aggr;

    PARM(2, OF);
    env->stck = pvec_pop(env->stck, &aggr);
    env->stck = pvec_pop(env->stck, &elem);
    switch (aggr.op) {
    case LIST_:
	i = pvec_cnt(aggr.u.lis) - elem.u.num - 1;
	elem = pvec_nth(aggr.u.lis, i);
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	elem.u.num = aggr.u.str[elem.u.num];
	elem.op = CHAR_;
	break;

    case SET_:
	for (j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		if (elem.u.num == 0) {
		    elem.u.num = i;
		    elem.op = INTEGER_;
		    break;
		}
		elem.u.num--;
	    }
	break;

    default:
	break;
    }
    env->stck = pvec_add(env->stck, elem);
}
#endif
