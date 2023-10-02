/*
    module  : choice.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef CHOICE_C
#define CHOICE_C

/**
OK 1330  choice  :  DDDA	B T F  ->  X
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
