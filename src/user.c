/*
    module  : user.c
    version : 1.3
    date    : 09/04/23
*/
#ifndef USER_C
#define USER_C

/**
OK 2380  user  :  DA	X  ->  B
Tests whether X is a user-defined symbol.
*/
void user_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    node.u.num = node.op == USR_;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
