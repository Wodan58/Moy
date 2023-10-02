/*
    module  : iffile.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef IFFILE_C
#define IFFILE_C

/**
OK 2680  iffile  :  DDDP	X [T] [E]  ->  ...
If X is a file, executes T else executes E.
*/
void iffile_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    node = pvec_lst(env->stck);
    node = node.op == FILE_ ? first : second;
    prog(env, node.u.lis);
}
#endif
