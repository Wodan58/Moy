/*
    module  : rem.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef REM_C
#define REM_C

/**
Q0  OK  1420  rem  :  DDA  I J  ->  K
Integer K is the remainder of dividing I by J.  Also supports float.
*/
void rem_(pEnv env)
{
    Node first, second;

    PARM(2, REM);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    switch (first.op) {
    case FLOAT_:
	switch (second.op) {
	case FLOAT_:
	    first.u.dbl = fmod(first.u.dbl, second.u.dbl);
	    break;

	default:
	    first.u.dbl = fmod(first.u.dbl, second.u.num);
	    break;
	}
	break;

    default:
	switch (second.op) {
	case FLOAT_:
	    second.u.dbl = fmod(first.u.num, second.u.dbl);
	    env->stck = pvec_add(env->stck, second);
	    return;

	default:
	    first.u.num %= second.u.num;
	    break;
	}
	break;
    }
    env->stck = pvec_add(env->stck, first);
}
#endif
