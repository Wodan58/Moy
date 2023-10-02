/*
    module  : divide.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef DIVIDE_C
#define DIVIDE_C

/**
OK 1410  /\0divide  :  DDA 	I J  ->  K
Integer K is the (rounded) ratio of integers I and J.  Also supports float.
*/
void divide_(pEnv env)
{
    Node first, second;

    PARM(2, DIVIDE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    switch (first.op) {
    case FLOAT_:
	switch (second.op) {
	case FLOAT_:
	    first.u.dbl /= second.u.dbl;
	    break;

	default:
	    first.u.dbl /= second.u.num;
	    break;
	}
	break;

    default:
	switch (second.op) {
	case FLOAT_:
	    second.u.dbl = first.u.num / second.u.dbl;
	    env->stck = pvec_add(env->stck, second);
	    return;

	default:
	    first.u.num /= second.u.num;
	    break;
	}
	break;
    }
    env->stck = pvec_add(env->stck, first);
}
#endif
