/*
    module  : maxint.c
    version : 1.12
    date    : 06/20/22
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
