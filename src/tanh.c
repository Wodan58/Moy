/*
    module  : tanh.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    node.u.dbl = tanh(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
