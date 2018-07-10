/*
    module  : clock.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef CLOCK_X
#define CLOCK_C

/**
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
#endif
