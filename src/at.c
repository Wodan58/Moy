/*
    module  : at.c
    version : 1.10
    date    : 03/05/24
*/
#ifndef AT_C
#define AT_C

/**
Q0  OK  2060  at  :  DDA  A I  ->  X
X (= A[I]) is the member of A at position I.
*/
void at_(pEnv env)
{
    int64_t i, j;
    Node elem, aggr;

    PARM(2, AT);
    env->stck = pvec_pop(env->stck, &elem);
    env->stck = pvec_pop(env->stck, &aggr);
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
    }
    env->stck = pvec_add(env->stck, elem);
}
#endif
