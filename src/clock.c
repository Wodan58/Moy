/*
    module  : clock.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef CLOCK_X
#define CLOCK_C

#ifdef NEW_RUNTIME
void do_clock(void)
{
    TRACE;
    do_push(clock() - startclock());
}
#else
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
#endif
