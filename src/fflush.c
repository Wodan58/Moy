/*
    module  : fflush.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
fflush  :  S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
PRIVATE void do_fflush(void)
{
#ifndef NCHECK
    COMPILE;
    ONEPARAM("fflush");
    FILE("fflush");
#endif
    fflush(stk->u.fil);
}
