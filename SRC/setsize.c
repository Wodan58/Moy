/*
    module  : setsize.c
    version : 1.4
    date    : 03/12/17
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
    COMPILE;
#endif
    PUSH(INTEGER_, SETSIZE_);
}
