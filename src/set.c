/*
    module  : set.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef SET_C
#define SET_C

/**
OK 2340  set  :  DA	X  ->  B
Tests whether X is a set.
*/
void set_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.op == SET_;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
