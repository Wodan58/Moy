/*
    module  : eql.c
    version : 1.3
    date    : 09/04/23
*/
#ifndef EQL_C
#define EQL_C

/**
OK 2270  =\0eql  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X equal to Y.  Also supports float.
*/
void eql_(pEnv env)
{
    Node first, second, node;

    PARM(2, ANYTYPE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node.u.num = Compare(env, first, second) == 0;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
