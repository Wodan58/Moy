/*
    module  : tanh.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef TANH_C
#define TANH_C

/**
OK 1680  tanh  :  DA	F  ->  G
G is the hyperbolic tangent of F.
*/
void tanh_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = tanh(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
