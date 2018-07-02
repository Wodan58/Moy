/*
    module  : fflush.c
    version : 1.5
    date    : 07/02/18
*/

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
