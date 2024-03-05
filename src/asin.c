/*
    module  : asin.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef ASIN_C
#define ASIN_C

/**
Q0  OK  1500  asin  :  DA  F  ->  G
G is the arc sine of F.
*/
void asin_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = asin(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
