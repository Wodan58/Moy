/*
    module  : integer.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef INTEGER_C
#define INTEGER_C

/**
OK 2330  integer  :  DA	X  ->  B
Tests whether X is an integer.
*/
void integer_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    node = vec_pop(env->stck);
    node.u.num = node.op == INTEGER_;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
