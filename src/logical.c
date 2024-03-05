/*
    module  : logical.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef LOGICAL_C
#define LOGICAL_C

/**
Q0  OK  2330  logical  :  DA  X  ->  B
Tests whether X is a logical.
*/
void logical_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.op == BOOLEAN_;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
