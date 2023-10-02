/*
    module  : cosh.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef COSH_C
#define COSH_C

/**
OK 1550  cosh  :  DA	F  ->  G
G is the hyperbolic cosine of F.
*/
void cosh_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = cosh(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
