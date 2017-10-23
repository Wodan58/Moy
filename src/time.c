/*
    module  : time.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
time  :  ->  I
Pushes the current time (in seconds since the Epoch).
*/
PRIVATE void do_time(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, time(0));
}
