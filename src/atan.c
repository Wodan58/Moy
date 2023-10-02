/*
    module  : atan.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef ATAN_C
#define ATAN_C

/**
OK 1510  atan  :  DA	F  ->  G
G is the arc tangent of F.
*/
void atan_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = atan(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
