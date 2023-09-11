/*
    module  : ifchar.c
    version : 1.5
    date    : 09/11/23
*/
#ifndef IFCHAR_C
#define IFCHAR_C

/**
OK 2620  ifchar  :  DDDP	X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
void ifchar_(pEnv env)
{
#ifndef COMPILER
    Node first, second, node;

    PARM(3, WHILE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node = lst_back(env->stck);
    node = node.op == CHAR_ ? first : second;
    prog(env, node.u.lis);
#endif
}
#endif
