/*
    module  : setsize.c
    version : 1.5
    date    : 04/09/17
*/
#include "runtime.h"

/*
setsize  :  ->  setsize
Pushes the maximum number of elements in a set (platform dependent).
Typically it is 32, and set members are in the range 0..31.
*/
PRIVATE void do_setsize(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(1);
    COMPILE;
#endif
    PUSH(INTEGER_, SETSIZE_);
}
