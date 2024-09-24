/*
    module  : rotate.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef ROTATE_C
#define ROTATE_C

/**
Q0  OK  1250  rotate  :  DDDAAA  X Y Z  ->  Z Y X
Interchanges X and Z.
*/
void rotate_(pEnv env)
{
    Node first, second, third;

    PARM(3, ANYTYPE);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    vec_push(env->stck, third);
    vec_push(env->stck, second);
    vec_push(env->stck, first);
}
#endif
