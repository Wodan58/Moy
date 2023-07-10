/*
    module  : string.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    node.u.num = node.op == STRING_;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
