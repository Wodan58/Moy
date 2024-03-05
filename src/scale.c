/*
    module  : scale.c
    version : 1.5
    date    : 03/05/24
*/
#ifndef SCALE_C
#define SCALE_C

/**
Q0  OK  3220  scale  :  D  I  ->
[NUM] Sets the number of digits to be used after the decimal point.
*/
void scale_(pEnv env)
{
#ifdef USE_BIGNUM_ARITHMETIC
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    env->scale = node.u.num;
#endif
}
#endif
