/*
    module  : maxint.c
    version : 1.6
    date    : 06/25/18
*/
#include "runtime.h"

/**
maxint  :  ->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
PRIVATE void do_maxint(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, MAXINT_);
}
