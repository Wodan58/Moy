/*
    module  : maxint.c
    version : 1.11
    date    : 03/15/21
*/
#ifndef MAXINT_C
#define MAXINT_C

/**
maxint  :  ->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
PRIVATE void do_maxint(pEnv env)
{
    PUSH_NUM(INTEGER_, MAXINT_);
}
/* maxint.c */
#endif
