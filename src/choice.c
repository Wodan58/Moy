/*
    module  : choice.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef CHOICE_C
#define CHOICE_C

/**
Q0  OK  1330  choice  :  DDDA  B T F  ->  X
If B is true, then X = T else X = F.
*/
void choice_(pEnv env)
{
    Node first, second, third;

    PARM(3, ANYTYPE);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first = first.u.num ? second : third;
    vec_push(env->stck, first);
}
#endif
