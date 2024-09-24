/*
    module  : rollup.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef ROLLUP_C
#define ROLLUP_C

/**
Q0  OK  1230  rollup  :  DDDAAA  X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
void rollup_(pEnv env)
{
    Node first, second, third;

    PARM(3, ANYTYPE);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    vec_push(env->stck, third);
    vec_push(env->stck, first);
    vec_push(env->stck, second);
}
#endif
