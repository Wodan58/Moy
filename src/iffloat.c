/*
    module  : iffloat.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef IFFLOAT_C
#define IFFLOAT_C

/**
OK 2670  iffloat  :  DDDP	X [T] [E]  ->  ...
If X is a float, executes T else executes E.
*/
void iffloat_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    node = pvec_lst(env->stck);
    node = node.op == FLOAT_ ? first : second;
    prog(env, node.u.lis);
}
#endif
