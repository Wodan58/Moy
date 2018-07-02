/*
    module  : time.c
    version : 1.6
    date    : 07/02/18
*/

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
