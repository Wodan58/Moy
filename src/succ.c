/*
    module  : succ.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef SUCC_C
#define SUCC_C

/**
Q0  OK  1800  succ  :  DA  M  ->  N
Numeric N is the successor of numeric M.
*/
void succ_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num++;
    env->stck = pvec_add(env->stck, node);
}
#endif
