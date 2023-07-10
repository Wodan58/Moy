/*
    module  : list.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef LIST_C
#define LIST_C

/**
OK 2380  list  :  DA	X  ->  B
Tests whether X is a list.
*/
void list_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = vec_pop(env->stck);
    node.u.num = node.op == LIST_;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
