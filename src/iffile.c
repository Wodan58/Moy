/*
    module  : iffile.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef IFFILE_C
#define IFFILE_C

/**
Q2  OK  2680  iffile  :  DDDP  X [T] [E]  ->  ...
[FOREIGN] If X is a file, executes T else executes E.
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
