/*
    module  : plus.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef PLUS_C
#define PLUS_C

/**
OK 1380  +\0plus  :  DDA	M I  ->  N
Numeric N is the result of adding integer I to numeric M.
Also supports float.
*/
void plus_(pEnv env)
{
    Node first, second;

    PARM(2, PLUSMINUS);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    switch (first.op) {
    case FLOAT_:
	switch (second.op) {
	case FLOAT_:
	    first.u.dbl += second.u.dbl;
	    break;

	default:
	    first.u.dbl += second.u.num;
	    break;
	}
	break;

    default:
	switch (second.op) {
	case FLOAT_:
	    second.u.dbl += first.u.num;
            vec_push(env->stck, second);
	    return;

	default:
            first.u.num += second.u.num;
	    break;
	}
	break;
    }
    vec_push(env->stck, first);
}
#endif
