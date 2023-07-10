/*
    module  : ifchar.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef IFCHAR_C
#define IFCHAR_C

/**
OK 2640  ifchar  :  DDDU	X [T] [E]  ->  ...
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
