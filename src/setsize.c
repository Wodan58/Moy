/*
    module  : setsize.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef SETSIZE_X
#define SETSIZE_C

#ifdef NEW_RUNTIME
void do_setsize(void)
{
    TRACE;
    do_push(SETSIZE_);
}
#else
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
#endif
