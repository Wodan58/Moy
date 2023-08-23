/*
    module  : ifchar.c
    version : 1.3
    date    : 08/23/23
*/
#ifndef IFCHAR_C
#define IFCHAR_C

/**
OK 2640  ifchar  :  DDDP	X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
void ifchar_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node = lst_back(env->stck);
    node = node.op == CHAR_ ? first : second;
    prog(env, node.u.lis);
}
#endif
