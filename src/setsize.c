/*
    module  : setsize.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef SETSIZE_C
#define SETSIZE_C

/**
setsize  :  ->  setsize
Pushes the maximum number of elements in a set (platform dependent).
Typically it is 32, and set members are in the range 0..31.
*/
PRIVATE void do_setsize(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, SETSIZE_);
}
#endif
