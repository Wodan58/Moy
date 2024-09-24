/*
    module  : sinh.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef SINH_C
#define SINH_C

/**
Q0  OK  1650  sinh  :  DA  F  ->  G
G is the hyperbolic sine of F.
*/
void sinh_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = vec_pop(env->stck);
    node.u.dbl = sinh(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
