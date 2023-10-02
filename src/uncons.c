/*
    module  : uncons.c
    version : 1.8
    date    : 10/02/23
*/
#ifndef UNCONS_C
#define UNCONS_C

/**
OK 2110  uncons  :  DAA	A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
void uncons_(pEnv env)
{
    int i = 0;
    Node aggr, elem, temp;

    PARM(1, FIRST);
    env->stck = pvec_pop(env->stck, &aggr);
    switch (aggr.op) {
    case LIST_:
	temp.u.lis = pvec_init();
	pvec_shallow_copy(temp.u.lis, aggr.u.lis);
	aggr.u.lis = pvec_pop(temp.u.lis, &elem);
	env->stck = pvec_add(env->stck, elem);	/* push element */
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	elem.u.num = *aggr.u.str++;
	elem.op = CHAR_;
	env->stck = pvec_add(env->stck, elem);	/* push element */
	aggr.u.str = GC_strdup(aggr.u.str);
	break;

    case SET_:
	while (!(aggr.u.set & ((int64_t)1 << i)))
	    i++;
	elem.u.num = i;
	elem.op = INTEGER_;
	env->stck = pvec_add(env->stck, elem);	/* push element */
	aggr.u.set &= ~((int64_t)1 << i);
	break;

    default:
	break;
    }
    env->stck = pvec_add(env->stck, aggr);	/* push remainder */
}
#endif
