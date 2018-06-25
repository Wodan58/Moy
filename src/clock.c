/*
    module  : clock.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

extern clock_t startclock;

/**
clock  :  ->  I
Pushes the integer value of current CPU usage in milliseconds.
*/
PRIVATE void do_clock(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, clock() - startclock);
}
