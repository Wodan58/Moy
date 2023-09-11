/*
    module  : float.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef FLOAT_C
#define FLOAT_C

/**
OK 2390  float  :  DA	R  ->  B
Tests whether R is a float.
*/
void float_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, ANYTYPE);
    node = lst_pop(env->stck);
    node.u.num = node.op == FLOAT_;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
#endif
}
#endif
