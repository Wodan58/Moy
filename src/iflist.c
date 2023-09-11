/*
    module  : iflist.c
    version : 1.5
    date    : 09/11/23
*/
#ifndef IFLIST_C
#define IFLIST_C

/**
OK 2660  iflist  :  DDDP	X [T] [E]  ->  ...
If X is a list, executes T else executes E.
*/
void iflist_(pEnv env)
{
#ifndef COMPILER
    Node first, second, node;

    PARM(3, WHILE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node = lst_back(env->stck);
    node = node.op == LIST_ ? first : second;
    prog(env, node.u.lis);
#endif
}
#endif
