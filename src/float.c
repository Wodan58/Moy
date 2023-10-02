/*
    module  : float.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef FLOAT_C
#define FLOAT_C

/**
OK 2390  float  :  DA	R  ->  B
Tests whether R is a float.
*/
void float_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.op == FLOAT_;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
