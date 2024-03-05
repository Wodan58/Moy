/*
    module  : radix.c
    version : 1.2
    date    : 03/05/24
*/
#ifndef RADIX_C
#define RADIX_C

/**
Q0  OK  3190  radix  :  D  I  ->
[NUM] Sets the output radix.
*/
void radix_(pEnv env)
{
#ifdef USE_BIGNUM_ARITHMETIC
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    env->radix = node.u.num;
#endif
}
#endif
