/*
    module  : rolldown.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef ROLLDOWN_C
#define ROLLDOWN_C

/**
rolldown  :  X Y Z  ->  Y Z X
Moves Y and Z down, moves X up.
*/
PRIVATE void do_rolldown(pEnv env)
{
    Node *first, *second, *third;

    THREEPARAMS("rolldown");
    first = env->stk;
    POP(env->stk);
    second = env->stk;
    POP(env->stk);
    third = env->stk;
    GUNARY(second->op, second->u);
    DUPLICATE(first);
    DUPLICATE(third);
}
#endif
