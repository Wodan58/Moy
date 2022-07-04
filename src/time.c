/*
    module  : time.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef TIME_C
#define TIME_C

/**
time  :  ->  I
Pushes the current time (in seconds since the Epoch).
*/
PRIVATE void do_time(pEnv env)
{
    COMPILE;
    PUSH_NUM(INTEGER_, time(0));
}
#endif
