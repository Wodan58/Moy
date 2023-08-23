/*
    module  : iffloat.c
    version : 1.3
    date    : 08/23/23
*/
#ifndef IFFLOAT_C
#define IFFLOAT_C

/**
OK 2690  iffloat  :  DDDP	X [T] [E]  ->  ...
If X is a float, executes T else executes E.
*/
void iffloat_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node = lst_back(env->stck);
    node = node.op == FLOAT_ ? first : second;
    prog(env, node.u.lis);
}
#endif
