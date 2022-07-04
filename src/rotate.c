/*
    module  : rotate.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef ROTATE_C
#define ROTATE_C

/**
rotate  :  X Y Z  ->  Z Y X
Interchanges X and Z.
*/
PRIVATE void do_rotate(pEnv env)
{
    Node *first, *second, *third;

    THREEPARAMS("rotate");
    first = env->stk;
    POP(env->stk);
    second = env->stk;
    POP(env->stk);
    third = env->stk;
    GUNARY(first->op, first->u);
    DUPLICATE(second);
    DUPLICATE(third);
}
#endif
