/*
    module  : srand.c
    version : 1.8
    date    : 07/20/18
*/
#ifndef SRAND_X
#define SRAND_C

#ifdef NEW_RUNTIME
void do_srand(void)
{
    TRACE;
    srand(do_pop());
}
#else
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
#endif
