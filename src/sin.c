/*
    module  : sin.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef SIN_C
#define SIN_C

/**
Q0  OK  1640  sin  :  DA  F  ->  G
G is the sine of F.
*/
void sin_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = vec_pop(env->stck);
    node.u.dbl = sin(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
