/*
    module  : clock.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

extern clock_t startclock;

/*
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
