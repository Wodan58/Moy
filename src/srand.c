/*
    module  : srand.c
    version : 1.5
    date    : 07/02/18
*/

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
