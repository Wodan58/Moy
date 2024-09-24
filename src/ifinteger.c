/*
    module  : ifinteger.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef IFINTEGER_C
#define IFINTEGER_C

/**
Q2  OK  2610  ifinteger  :  DDDP  X [T] [E]  ->  ...
If X is an integer, executes T else executes E.
*/
void ifinteger_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node = vec_back(env->stck);
    node = node.op == INTEGER_ ? first : second;
    prog(env, node.u.lis);
}
#endif
