/*
    module  : tan.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef TAN_C
#define TAN_C

/**
Q0  OK  1670  tan  :  DA  F  ->  G
G is the tangent of F.
*/
void tan_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = tan(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
