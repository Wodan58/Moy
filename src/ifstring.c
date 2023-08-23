/*
    module  : ifstring.c
    version : 1.3
    date    : 08/23/23
*/
#ifndef IFSTRING_C
#define IFSTRING_C

/**
OK 2670  ifstring  :  DDDP 	X [T] [E]  ->  ...
If X is a string, executes T else executes E.
*/
void ifstring_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node = lst_back(env->stck);
    node = node.op == STRING_ ? first : second;
    prog(env, node.u.lis);
}
#endif
