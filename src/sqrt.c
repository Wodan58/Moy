/*
    module  : sqrt.c
    version : 1.8
    date    : 09/17/24
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
    node = vec_pop(env->stck);
    node.u.dbl = sqrt(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
