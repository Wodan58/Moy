/*
    module  : fflush.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
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
