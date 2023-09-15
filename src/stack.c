/*
    module  : stack.c
    version : 1.5
    date    : 09/15/23
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

    lst_init(node.u.lis);
    lst_copy(node.u.lis, env->stck);
    node.op = LIST_;
    lst_push(env->stck, node);
}
#endif
