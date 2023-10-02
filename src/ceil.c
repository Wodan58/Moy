/*
    module  : ceil.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef CEIL_C
#define CEIL_C

/**
OK 1530  ceil  :  DA	F  ->  G
G is the float ceiling of F.
*/
void ceil_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = ceil(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
