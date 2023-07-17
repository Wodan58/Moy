/*
    module  : iffile.c
    version : 1.2
    date    : 07/17/23
*/
#ifndef IFFILE_C
#define IFFILE_C

/**
OK 2700  iffile  :  DDDP	X [T] [E]  ->  ...
If X is a file, executes T else executes E.
*/
void iffile_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node = vec_back(env->stck);
    node = node.op == FILE_ ? first : second;
    prog(env, node.u.lis);
}
#endif
