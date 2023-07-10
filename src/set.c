/*
    module  : set.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef SET_C
#define SET_C

/**
OK 2360  set  :  DA	X  ->  B
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
