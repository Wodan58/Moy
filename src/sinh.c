/*
    module  : sinh.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    node.u.dbl = sinh(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
