/*
    module  : rem.c
    version : 1.5
    date    : 09/15/23
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
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
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
	    lst_push(env->stck, second);
	    return;

	default:
	    first.u.num %= second.u.num;
	    break;
	}
	break;
    }
    lst_push(env->stck, first);
}
#endif
