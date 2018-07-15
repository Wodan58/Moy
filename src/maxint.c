/*
    module  : maxint.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef MAXINT_X
#define MAXINT_C

#ifdef NEW_RUNTIME
void do_maxint(void)
{
    TRACE;
    do_push(MAXINT_);
}
#else
/**
maxint  :  ->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
PRIVATE void do_maxint(void)
{
    PUSH(INTEGER_, MAXINT_);
}
/* maxint.c */
#endif
#endif
