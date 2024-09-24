/*
    module  : rolldown.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef ROLLDOWN_C
#define ROLLDOWN_C

/**
Q0  OK  1240  rolldown  :  DDDAAA  X Y Z  ->  Y Z X
Moves Y and Z down, moves X up.
*/
void rolldown_(pEnv env)
{
    Node first, second, third;

    PARM(3, ANYTYPE);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    vec_push(env->stck, second);
    vec_push(env->stck, third);
    vec_push(env->stck, first);
}
#endif
