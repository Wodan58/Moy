/*
    module  : cosh.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef COSH_C
#define COSH_C

/**
Q0  OK  1550  cosh  :  DA  F  ->  G
G is the hyperbolic cosine of F.
*/
void cosh_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = vec_pop(env->stck);
    node.u.dbl = cosh(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
