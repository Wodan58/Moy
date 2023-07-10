/*
    module  : logical.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef LOGICAL_C
#define LOGICAL_C

/**
OK 2350  logical  :  DA	X  ->  B
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
