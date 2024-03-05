/*
    module  : sqrt.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef SQRT_C
#define SQRT_C

/**
Q0  OK  1660  sqrt  :  DA  F  ->  G
G is the square root of F.
*/
void sqrt_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = sqrt(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
