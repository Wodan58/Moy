/*
    module  : stack.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef STACK_C
#define STACK_C

/**
OK 1040  stack  :  A	.. X Y Z  ->  .. X Y Z [Z Y X ..]
Pushes the stack as a list.
*/
PRIVATE void stack_(pEnv env)
{
    Node node;

    vec_init(node.u.lis);
    vec_copy(node.u.lis, env->stck);
    node.op = LIST_;
    vec_push(env->stck, node);
}
#endif
