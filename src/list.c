/*
    module  : list.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef LIST_C
#define LIST_C

/**
Q0  OK  2360  list  :  DA  X  ->  B
Tests whether X is a list.
*/
void list_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.op == LIST_;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
