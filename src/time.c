/*
    module  : time.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef TIME_C
#define TIME_C

/**
time  :  ->  I
Pushes the current time (in seconds since the Epoch).
*/
PRIVATE void do_time(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, time(0));
}
#endif
