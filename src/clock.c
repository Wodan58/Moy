/*
    module  : clock.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef CLOCK_C
#define CLOCK_C

/**
clock  :  ->  I
Pushes the integer value of current CPU usage in milliseconds.
*/
PRIVATE void do_clock(pEnv env)
{
    COMPILE;
    PUSH_NUM(INTEGER_, (clock() - startclock));
}
#endif
