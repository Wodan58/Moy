/*
    module  : srand.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
srand  :  I  ->
Sets the random integer seed to integer I.
*/
PRIVATE void do_srand(void)
{
#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("srand");
    INTEGER("srand");
#endif
    srand(stk->u.num);
    POP(stk);
}
