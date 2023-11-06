/*
    module  : times.c
    version : 1.7
    date    : 11/06/23
*/
#ifndef TIMES_C
#define TIMES_C

/**
OK 2800  times  :  DDA	N [P]  ->  ...
N times executes P.
*/
void times_(pEnv env)
{
    Node list, node;

    PARM(2, TIMES);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &node);
    while (node.u.num--)
	prog(env, list.u.lis);
}
#endif
