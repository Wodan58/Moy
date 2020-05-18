/*
    module  : maxint.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef MAXINT_C
#define MAXINT_C

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
