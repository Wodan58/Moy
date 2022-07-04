/*
    module  : stack.c
    version : 1.14
    date    : 06/20/22
*/
#ifndef STACK_C
#define STACK_C

/**
stack  :  .. X Y Z  ->  .. X Y Z [Z Y X ..]
Pushes the stack as a list.
*/
PRIVATE void do_stack(pEnv env)
{
    COMPILE;
    PUSH_PTR(LIST_, env->stk);
}
#endif
