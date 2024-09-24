/*
    module  : set.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef SET_C
#define SET_C

/**
Q0  OK  2340  set  :  DA  X  ->  B
Tests whether X is a set.
*/
void set_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = vec_pop(env->stck);
    node.u.num = node.op == SET_;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
