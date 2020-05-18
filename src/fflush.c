/*
    module  : fflush.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef FFLUSH_C
#define FFLUSH_C

/**
fflush  :  S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
PRIVATE void do_fflush(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ONEPARAM("fflush");
    FILE("fflush");
    fflush(stk->u.fil);
}
#endif
