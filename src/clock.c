/*
    module  : clock.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef CLOCK_C
#define CLOCK_C

/**
clock  :  ->  I
Pushes the integer value of current CPU usage in milliseconds.
*/
PRIVATE void do_clock(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, clock() - startclock);
}
#endif
