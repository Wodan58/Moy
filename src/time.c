/*
    module  : time.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef TIME_X
#define TIME_C

#ifdef NEW_RUNTIME
void do_time(void)
{
    TRACE;
    do_push(time(0));
}
#else
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
#endif
