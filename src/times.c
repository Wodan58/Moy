/*
    module  : times.c
    version : 1.2
    date    : 08/23/23
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
    list = lst_pop(env->stck);
    node = lst_pop(env->stck);
    for (i = node.u.num; i; i--)
        prog(env, list.u.lis);
}
#endif
