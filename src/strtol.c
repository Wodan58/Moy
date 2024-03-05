/*
    module  : strtol.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef STRTOL_C
#define STRTOL_C

/**
Q0  OK  1740  strtol  :  DDA  S I  ->  J
String S is converted to the integer J using base I.
If I = 0, assumes base 10,
but leading "0" means base 8 and leading "0x" means base 16.
*/
void strtol_(pEnv env)
{
    Node first, second;

    PARM(2, STRTOL);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    first.u.num = strtol(first.u.str, 0, second.u.num);
    first.op = INTEGER_;
    env->stck = pvec_add(env->stck, first);
}
#endif
