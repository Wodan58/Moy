/*
    module  : times.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef TIMES_C
#define TIMES_C

/**
OK 2820  times  :  DDU	N [P]  ->  ...
N times executes P.
*/
void times_(pEnv env)
{
    int i;
    Node node, list;

    PARM(2, TIMES);
    list = vec_pop(env->stck);
    node = vec_pop(env->stck);
    for (i = node.u.num; i; i--)
        prog(env, list.u.lis);
}
#endif
