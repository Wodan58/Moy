/*
    module  : user.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef USER_C
#define USER_C

/**
OK 2400  user  :  DA	X  ->  B
Tests whether X is a user-defined symbol.
*/
void user_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = vec_pop(env->stck);
    node.u.num = node.op == USR_;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
