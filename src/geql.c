/*
    module  : geql.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef GEQL_C
#define GEQL_C

/**
OK 2230  >=\0geql  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X greater than or equal to Y.  Also supports float.
*/
void geql_(pEnv env)
{
    Node first, second, node;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    if (first.op == SET_ || second.op == SET_)
        node.u.num = !(second.u.set & ~first.u.set);
    else
        node.u.num = Compare(env, first, second) >= 0;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
