/*
    module  : times.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef TIMES_C
#define TIMES_C

/**
OK 2800  times  :  DDU	N [P]  ->  ...
N times executes P.
*/
void times_(pEnv env)
{
#ifndef COMPILER
    int i;
    Node node, list;

    PARM(2, TIMES);
    list = lst_pop(env->stck);
    node = lst_pop(env->stck);
    for (i = node.u.num; i; i--)
	prog(env, list.u.lis);
#endif
}
#endif
