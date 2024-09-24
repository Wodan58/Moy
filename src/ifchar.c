/*
    module  : ifchar.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef IFCHAR_C
#define IFCHAR_C

/**
Q2  OK  2620  ifchar  :  DDDP  X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
void ifchar_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node = vec_back(env->stck);
    node = node.op == CHAR_ ? first : second;
    prog(env, node.u.lis);
}
#endif
