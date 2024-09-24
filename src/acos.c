/*
    module  : acos.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef ACOS_C
#define ACOS_C

/**
Q0  OK  1490  acos  :  DA  F  ->  G
G is the arc cosine of F.
*/
void acos_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = vec_pop(env->stck);
    node.u.dbl = acos(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
