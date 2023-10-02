/*
    module  : sinh.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef SINH_C
#define SINH_C

/**
OK 1650  sinh  :  DA	F  ->  G
G is the hyperbolic sine of F.
*/
void sinh_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = sinh(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
