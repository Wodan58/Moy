/*
    module  : integer.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef INTEGER_C
#define INTEGER_C

/**
OK 2310  integer  :  DA	X  ->  B
Tests whether X is an integer.
*/
void integer_(pEnv env)
{
    Node node;

    PARM(1, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    node.u.num = node.op == INTEGER_;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
