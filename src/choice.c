/*
    module  : choice.c
    version : 1.5
    date    : 09/15/23
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
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    first = first.u.num ? second : third;
    lst_push(env->stck, first);
}
#endif
