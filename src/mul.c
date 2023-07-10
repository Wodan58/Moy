/*
    module  : mul.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef MUL_C
#define MUL_C

/**
OK 1400  *\0ast  :  DDA	I J  ->  K
Integer K is the product of integers I and J.  Also supports float.
*/
void mul_(pEnv env)
{
    Node first, second;

    PARM(2, BFLOAT);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    switch (first.op) {
    case FLOAT_:
	switch (second.op) {
	case FLOAT_:
	    first.u.dbl *= second.u.dbl;
	    break;

	default:
	    first.u.dbl *= second.u.num;
	    break;
	}
	break;

    default:
	switch (second.op) {
	case FLOAT_:
	    second.u.dbl *= first.u.num;
            vec_push(env->stck, second);
	    return;

	default:
            first.u.num *= second.u.num;
	    break;
	}
	break;
    }
    vec_push(env->stck, first);
}
#endif
