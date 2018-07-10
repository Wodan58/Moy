/*
    module  : maxint.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef MAXINT_X
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
