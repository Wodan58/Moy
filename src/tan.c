/*
    module  : tan.c
    version : 1.8
    date    : 09/17/24
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
    node = vec_pop(env->stck);
    node.u.dbl = tan(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
