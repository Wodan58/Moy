/*
    module  : setsize.c
    version : 1.7
    date    : 07/02/18
*/

/**
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
