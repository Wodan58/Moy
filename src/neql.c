/*
    module  : neql.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef NEQL_C
#define NEQL_C

/**
OK 2270  !=\0neql  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X not equal to Y.  Also supports float.
*/
void neql_(pEnv env)
{
    Node first, second, node;

    PARM(2, ANYTYPE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node.u.num = Compare(env, first, second) != 0;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
