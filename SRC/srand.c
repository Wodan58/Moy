/*
    module  : srand.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
srand  :  I  ->
Sets the random integer seed to integer I.
*/
PRIVATE void do_srand(void)
{
#ifndef NCHECK
    COMPILE;
    ONEPARAM("srand");
    INTEGER("srand");
#endif
    srand(stk->u.num);
    POP(stk);
}
