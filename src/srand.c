/*
    module  : srand.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef SRAND_C
#define SRAND_C

/**
srand  :  I  ->
Sets the random integer seed to integer I.
*/
PRIVATE void do_srand(pEnv env)
{
    COMPILE;
    ONEPARAM("srand");
    INTEGER("srand");
    srand(env->stk->u.num);
    POP(env->stk);
}
#endif
