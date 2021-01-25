/*
    module  : srand.c
    version : 1.10
    date    : 01/24/21
*/
#ifndef SRAND_C
#define SRAND_C

void my_srand(unsigned num);

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
    my_srand(stk->u.num);
    POP(stk);
}
#endif
