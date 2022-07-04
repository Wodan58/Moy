/*
    module  : strtol.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef STRTOL_C
#define STRTOL_C

/**
strtol  :  S I  ->  J
String S is converted to the integer J using base I.
If I = 0, assumes base 10,
but leading "0" means base 8 and leading "0x" means base 16.
*/
PRIVATE void do_strtol(pEnv env)
{
    int base;

    TWOPARAMS("strtol");
    INTEGER("strtol");
    base = env->stk->u.num;
    POP(env->stk);
    STRING("strtol");
    UNARY(INTEGER_NEWNODE, strtol(env->stk->u.str, 0, base));
}
#endif
