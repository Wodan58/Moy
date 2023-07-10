/*
    module  : dupd.c
    version : 1.1
    date    : 07/10/23
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
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    vec_push(env->stck, first);
    vec_push(env->stck, first);
    vec_push(env->stck, second);
}
#endif
