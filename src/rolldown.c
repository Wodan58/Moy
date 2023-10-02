/*
    module  : rolldown.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef ROLLDOWN_C
#define ROLLDOWN_C

/**
OK 1240  rolldown  :  DDDAAA	X Y Z  ->  Y Z X
Moves Y and Z down, moves X up.
*/
void rolldown_(pEnv env)
{
    Node first, second, third;

    PARM(3, ANYTYPE);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    env->stck = pvec_add(env->stck, second);
    env->stck = pvec_add(env->stck, third);
    env->stck = pvec_add(env->stck, first);
}
#endif
