/*
    module  : time.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef TIME_X
#define TIME_C

/**
time  :  ->  I
Pushes the current time (in seconds since the Epoch).
*/
PRIVATE void do_time(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, time(0));
}
#endif
