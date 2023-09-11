/*
    module  : tanh.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef TANH_C
#define TANH_C

/**
OK 1680  tanh  :  DA	F  ->  G
G is the hyperbolic tangent of F.
*/
void tanh_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = tanh(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
