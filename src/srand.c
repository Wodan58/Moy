/*
    module  : srand.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef SRAND_C
#define SRAND_C

void my_srand(unsigned num);

/**
srand  :  I  ->
Sets the random integer seed to integer I.
*/
PRIVATE void do_srand(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("srand");
    INTEGER("srand");
    my_srand(env->stk->u.num);
    POP(env->stk);
}
#endif
