/*
    module  : of.c
    version : 1.11
    date    : 09/17/24
*/
#ifndef OF_C
#define OF_C

/**
Q0  OK  2070  of  :  DDA  I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
void of_(pEnv env)
{
    int64_t i, j;
    Node aggr, elem;

    PARM(2, OF);
    aggr = vec_pop(env->stck);
    elem = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	i = vec_size(aggr.u.lis) - elem.u.num - 1;
	elem = vec_at(aggr.u.lis, i);
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
    }
    vec_push(env->stck, elem);
}
#endif
