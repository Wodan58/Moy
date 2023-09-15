/*
    module  : rollup.c
    version : 1.5
    date    : 09/15/23
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
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    lst_push(env->stck, third);
    lst_push(env->stck, first);
    lst_push(env->stck, second);
}
#endif
