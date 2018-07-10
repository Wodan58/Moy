/*
    module  : srand.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef SRAND_X
#define SRAND_C

/**
srand  :  I  ->
Sets the random integer seed to integer I.
*/
PRIVATE void do_srand(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("srand");
    INTEGER("srand");
    srand(stk->u.num);
    POP(stk);
}
#endif
