/*
    module  : set.c
    version : 1.5
    date    : 09/15/23
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
    node = lst_pop(env->stck);
    node.u.num = node.op == SET_;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
