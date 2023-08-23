/*
    module  : compare.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef COMPARE_C
#define COMPARE_C

/**
OK 2060  compare  :  DDA	A B  ->  I
I (=-1,0,+1) is the comparison of aggregates A and B.
The values correspond to the predicates <=, =, >=.
*/
void compare_(pEnv env)
{
    Node first, second;

    PARM(2, ANYTYPE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    first.u.num = Compare(env, first, second);
    first.op = INTEGER_;
    lst_push(env->stck, first);
}
#endif
