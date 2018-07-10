/*
    module  : fflush.c
    version : 1.6
    date    : 07/10/18
*/
#ifndef FFLUSH_X
#define FFLUSH_C

/**
fflush  :  S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
PRIVATE void do_fflush(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ONEPARAM("fflush");
    FILE("fflush");
    fflush(stk->u.fil);
}
#endif
