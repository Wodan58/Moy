/*
    module  : time.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
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
