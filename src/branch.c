/*
    module  : branch.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef BRANCH_C
#define BRANCH_C

/**
Q2  OK  2590  branch  :  DDDP  B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
void branch_(pEnv env)
{
    Node first, second, third;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    first = first.u.num ? second : third;
    prog(env, first.u.lis);
}
#endif
