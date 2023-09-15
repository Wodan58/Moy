/*
    module  : max.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef MAX_C
#define MAX_C

/**
OK 1810  max  :  DDA	N1 N2  ->  N
N is the maximum of numeric values N1 and N2.  Also supports float.
*/
void max_(pEnv env)
{
    Node first, second;

    PARM(2, MAXMIN);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    switch (first.op) {
    case FLOAT_:
	switch (second.op) {
	case FLOAT_:
	    if (second.u.dbl > first.u.dbl)
		first.u.dbl = second.u.dbl;
	    break;

	default:
	    if (second.u.num > first.u.dbl)
		first.u.dbl = second.u.num;
	    break;
	}
	break;

    default:
	switch (second.op) {
	case FLOAT_:
	    if (first.u.num > second.u.dbl)
		second.u.dbl = first.u.num;
	    lst_push(env->stck, second);
	    return;

	default:
	    if (second.u.num > first.u.num)
		first.u.num = second.u.num;
	    break;
	}
	break;
    }
    lst_push(env->stck, first);
}
#endif
