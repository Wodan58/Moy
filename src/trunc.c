/*
    module  : trunc.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    node.u.num = node.u.dbl;
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
