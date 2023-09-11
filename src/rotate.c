/*
    module  : rotate.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef ROTATE_C
#define ROTATE_C

/**
OK 1250  rotate  :  DDDAAA 	X Y Z  ->  Z Y X
Interchanges X and Z.
*/
void rotate_(pEnv env)
{
#ifndef COMPILER
    Node first, second, third;

    PARM(3, ANYTYPE);
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    lst_push(env->stck, third);
    lst_push(env->stck, second);
    lst_push(env->stck, first);
#endif
}
#endif
