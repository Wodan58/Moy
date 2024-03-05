/*
    module  : choice.c
    version : 1.7
    date    : 03/05/24
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
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    first = first.u.num ? second : third;
    env->stck = pvec_add(env->stck, first);
}
#endif
