/*
    module  : logical.c
    version : 1.8
    date    : 09/17/24
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
    node = vec_pop(env->stck);
    node.u.num = node.op == BOOLEAN_;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
