/*
    module  : clock.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef CLOCK_C
#define CLOCK_C

/**
clock  :  ->  I
Pushes the integer value of current CPU usage in milliseconds.
*/
PRIVATE void do_clock(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, clock() - startclock);
}
#endif
