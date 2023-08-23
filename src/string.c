/*
    module  : string.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef STRING_C
#define STRING_C

/**
OK 2370  string  :  DA	X  ->  B
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
