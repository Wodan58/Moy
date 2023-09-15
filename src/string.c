/*
    module  : string.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef STRING_C
#define STRING_C

/**
OK 2350  string  :  DA	X  ->  B
Tests whether X is a string.
*/
void string_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    node.u.num = node.op == STRING_;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
