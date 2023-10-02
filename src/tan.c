/*
    module  : tan.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef TAN_C
#define TAN_C

/**
OK 1670  tan  :  DA	F  ->  G
G is the tangent of F.
*/
void tan_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = tan(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
