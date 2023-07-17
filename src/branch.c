/*
    module  : branch.c
    version : 1.2
    date    : 07/17/23
*/
#ifndef BRANCH_C
#define BRANCH_C

/**
OK 2610  branch  :  DDDP	B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
void branch_(pEnv env)
{
    Node first, second, third;

    PARM(3, WHILE);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    first = first.u.num ? second : third;
    prog(env, first.u.lis);
}
#endif
