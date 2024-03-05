/*
    module  : log10.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef LOG10_C
#define LOG10_C

/**
Q0  OK  1610  log10  :  DA  F  ->  G
G is the common logarithm of F.
*/
void log10_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = log10(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
