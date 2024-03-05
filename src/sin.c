/*
    module  : sin.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef SIN_C
#define SIN_C

/**
Q0  OK  1640  sin  :  DA  F  ->  G
G is the sine of F.
*/
void sin_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = sin(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
