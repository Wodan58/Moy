/*
    module  : dup.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef DUP_C
#define DUP_C

/**
dup  :  X  ->  X X
Pushes an extra copy of X onto stack.
*/
PRIVATE void do_dup(pEnv env)
{
    ONEPARAM("dup");
    DUPLICATE(env->stk);
}
#endif
