/*
    module  : rem.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef REM_C
#define REM_C

/**
OK 1420  rem  :  DDA	I J  ->  K
Integer K is the remainder of dividing I by J.  Also supports float.
*/
void rem_(pEnv env)
{
    Node first, second;

    PARM(2, REM);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
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
            vec_push(env->stck, second);
	    return;

	default:
            first.u.num %= second.u.num;
	    break;
	}
	break;
    }
    vec_push(env->stck, first);
}
#endif
