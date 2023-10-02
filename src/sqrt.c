/*
    module  : sqrt.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef SQRT_C
#define SQRT_C

/**
OK 1660  sqrt  :  DA	F  ->  G
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
