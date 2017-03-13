/*
    module  : clock.c
    version : 1.3
    date    : 03/12/17
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
    COMPILE;
#endif
    PUSH(INTEGER_, clock() - startclock);
}
