/*
    module  : stack.c
    version : 1.8
    date    : 03/21/24
*/
#ifndef STACK_C
#define STACK_C

/**
Q0  OK  1040  stack  :  A  .. X Y Z  ->  .. X Y Z [Z Y X ..]
Pushes the stack as a list.
*/
void stack_(pEnv env)
{
    Node node;

    node.u.lis = pvec_init();
    pvec_copy(node.u.lis, env->stck);
    node.op = LIST_;
    env->stck = pvec_add(env->stck, node);
}
#endif
