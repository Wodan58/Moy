/*
    module  : list.c
    version : 1.2
    date    : 08/23/23
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
    node = lst_pop(env->stck);
    node.u.num = node.op == LIST_;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
