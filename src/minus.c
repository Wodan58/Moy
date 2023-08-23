/*
    module  : minus.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef MINUS_C
#define MINUS_C

/**
OK 1390  -\0minus  :  DDA	M I  ->  N
Numeric N is the result of subtracting integer I from numeric M.
Also supports float.
*/
void minus_(pEnv env)
{
    Node first, second;

    PARM(2, PLUSMINUS);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    switch (first.op) {
    case FLOAT_:
	switch (second.op) {
	case FLOAT_:
	    first.u.dbl -= second.u.dbl;
	    break;

	default:
	    first.u.dbl -= second.u.num;
	    break;
	}
	break;

    default:
	switch (second.op) {
	case FLOAT_:
            second.u.dbl = first.u.num - second.u.dbl;
            lst_push(env->stck, second);
	    return;

	default:
            first.u.num -= second.u.num;
	    break;
	}
	break;
    }
    lst_push(env->stck, first);
}
#endif
