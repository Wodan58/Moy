/*
    module  : ifstring.c
    version : 1.2
    date    : 07/17/23
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
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node = vec_back(env->stck);
    node = node.op == STRING_ ? first : second;
    prog(env, node.u.lis);
}
#endif
