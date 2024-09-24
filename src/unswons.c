/*
    module  : unswons.c
    version : 1.11
    date    : 09/17/24
*/
#ifndef UNSWONS_C
#define UNSWONS_C

/**
Q0  OK  2120  unswons  :  DAA  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
void unswons_(pEnv env)
{
    int i = 0;
    Node aggr, elem, temp;

    PARM(1, FIRST);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
        vec_shallow_copy(temp.u.lis, aggr.u.lis);
        elem = vec_pop(temp.u.lis);
	aggr.u.lis = temp.u.lis;
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	elem.u.num = *aggr.u.str++;
	elem.op = CHAR_;
	aggr.u.str = GC_strdup(aggr.u.str);  
	break;

    case SET_:
	while (!(aggr.u.set & ((int64_t)1 << i)))
	    i++;
	elem.u.num = i;
	elem.op = INTEGER_;
	aggr.u.set &= ~((int64_t)1 << i);
	break;
    }
    vec_push(env->stck, aggr);
    vec_push(env->stck, elem);
}
#endif
