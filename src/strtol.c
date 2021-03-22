/*
    module  : strtol.c
    version : 1.11
    date    : 03/15/21
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
    long_t num;

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1 && STRING_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("strtol");
    INTEGER("strtol");
    base = env->stk->u.num;
    POP(env->stk);
    STRING("strtol");
    num = strtol(env->stk->u.str, 0, base);
    env->stk->u.num = num;
    env->stk->op = INTEGER_;
}
#endif
