/*
    module  : rollup.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef ROLLUP_C
#define ROLLUP_C

/**
rollup  :  X Y Z  ->  Z X Y
Moves X and Y up, moves Z down.
*/
PRIVATE void do_rollup(pEnv env)
{
    Node *first, *second, *third;

    THREEPARAMS("rollup");
    first = env->stk;
    POP(env->stk);
    second = env->stk;
    POP(env->stk);
    third = env->stk;
    GUNARY(first->op, first->u);
    DUPLICATE(third);
    DUPLICATE(second);
}
#endif
