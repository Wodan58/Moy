/*
    module  : time.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
time  :  ->  I
Pushes the current time (in seconds since the Epoch).
*/
PRIVATE void do_time(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, time(0));
}
