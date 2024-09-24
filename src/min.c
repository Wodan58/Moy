/*
    module  : min.c
    version : 1.8
    date    : 09/17/24
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
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
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
	    vec_push(env->stck, second);
	    return;

	default:
	    if (second.u.num < first.u.num)
		first.u.num = second.u.num;
	    break;
	}
	break;
    }
    vec_push(env->stck, first);
}
#endif
