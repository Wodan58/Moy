/*
    module  : time.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef TIME_C
#define TIME_C

/**
time  :  ->  I
Pushes the current time (in seconds since the Epoch).
*/
PRIVATE void do_time(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(INTEGER_, time(0));
}
#endif
