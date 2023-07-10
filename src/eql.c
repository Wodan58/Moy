/*
    module  : eql.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef EQL_C
#define EQL_C

/**
OK 2280  =\0eql  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X equal to Y.  Also supports float.
*/
void eql_(pEnv env)
{
    Node first, second, node;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node.u.num = Compare(env, first, second) == 0;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
