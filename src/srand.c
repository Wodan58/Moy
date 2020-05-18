/*
    module  : srand.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef SRAND_C
#define SRAND_C

/**
srand  :  I  ->
Sets the random integer seed to integer I.
*/
PRIVATE void do_srand(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("srand");
    INTEGER("srand");
    srand(stk->u.num);
    POP(stk);
}
#endif
