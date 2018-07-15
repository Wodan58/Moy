/*
    module  : fflush.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef FFLUSH_X
#define FFLUSH_C

#ifdef NEW_RUNTIME
void do_fflush(void)
{
    TRACE;
    fflush((FILE *)stk[-1]);
}
#else
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
#endif
