/*
    module  : stack.c
    version : 1.9
    date    : 09/17/24
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

    vec_copy_count(node.u.lis, env->stck, vec_size(env->stck));
    node.op = LIST_;
    vec_push(env->stck, node);
}
#endif
