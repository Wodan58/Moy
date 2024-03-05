/*
    module  : sign.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef SIGN_C
#define SIGN_C

/**
Q0  OK  1440  sign  :  DA  N1  ->  N2
Integer N2 is the sign (-1 or 0 or +1) of integer N1,
or float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1.
*/
void sign_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    if (node.op == FLOAT_)
	node.u.dbl = node.u.dbl < 0 ? -1 : node.u.dbl > 0;
    else
	node.u.num = node.u.num < 0 ? -1 : node.u.num > 0;
    env->stck = pvec_add(env->stck, node);
}
#endif
