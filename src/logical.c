/*
    module  : logical.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef LOGICAL_C
#define LOGICAL_C

/**
OK 2330  logical  :  DA	X  ->  B
Tests whether X is a logical.
*/
void logical_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    node.u.num = node.op == BOOLEAN_;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
