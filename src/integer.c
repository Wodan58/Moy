/*
    module  : integer.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef INTEGER_C
#define INTEGER_C

/**
Q0  OK  2310  integer  :  DA  X  ->  B
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
