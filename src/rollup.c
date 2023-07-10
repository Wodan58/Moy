/*
    module  : rollup.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef ROLLUP_C
#define ROLLUP_C

/**
OK 1230  rollup  :  DDDAAA 	X Y Z  ->  Z X Y
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
