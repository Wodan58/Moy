/*
    module  : sametype.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef SAMETYPE_C
#define SAMETYPE_C

/**
sametype  :  X Y  ->  B
Tests whether X and Y have the same type.
*/
PRIVATE void do_sametype(pEnv env)
{
    TWOPARAMS("sametype");
    BINARY(BOOLEAN_NEWNODE, env->stk->op == env->stk->next->op);
}
#endif
