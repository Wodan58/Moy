/*
    module  : maxint.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
maxint  :  ->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
PRIVATE void do_maxint(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, MAXINT_);
}
