/*
    module  : min.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef MIN_C
#define MIN_C

/**
Q0  OK  1820  min  :  DDA  N1 N2  ->  N
N is the minimum of numeric values N1 and N2.  Also supports float.
*/
void min_(pEnv env)
{
    Node first, second;

    PARM(2, MAXMIN);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    switch (first.op) {
    case FLOAT_:
	switch (second.op) {
	case FLOAT_:
	    if (second.u.dbl < first.u.dbl)
		first.u.dbl = second.u.dbl;
	    break;

	default:
	    if (second.u.num < first.u.dbl)
		first.u.dbl = second.u.num;
	    break;
	}
	break;

    default:
	switch (second.op) {
	case FLOAT_:
	    if (first.u.num < second.u.dbl)
		second.u.dbl = first.u.num;
	    env->stck = pvec_add(env->stck, second);
	    return;

	default:
	    if (second.u.num < first.u.num)
		first.u.num = second.u.num;
	    break;
	}
	break;
    }
    env->stck = pvec_add(env->stck, first);
}
#endif
