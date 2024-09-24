/*
    module  : sign.c
    version : 1.8
    date    : 09/17/24
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
    node = vec_pop(env->stck);
    if (node.op == FLOAT_)
	node.u.dbl = node.u.dbl < 0 ? -1 : node.u.dbl > 0;
    else
	node.u.num = node.u.num < 0 ? -1 : node.u.num > 0;
    vec_push(env->stck, node);
}
#endif
