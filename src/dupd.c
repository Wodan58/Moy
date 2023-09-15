/*
    module  : dupd.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef DUPD_C
#define DUPD_C

/**
OK 1270  dupd  :  DDAAA	Y Z  ->  Y Y Z
As if defined by:   dupd  ==  [dup] dip
*/
void dupd_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    lst_push(env->stck, first);
    lst_push(env->stck, first);
    lst_push(env->stck, second);
}
#endif
