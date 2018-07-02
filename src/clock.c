/*
    module  : clock.c
    version : 1.6
    date    : 07/02/18
*/

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
