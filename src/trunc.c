/*
    module  : trunc.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef TRUNC_C
#define TRUNC_C

/**
OK 1690  trunc  :  DA	F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
void trunc_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.u.dbl;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
