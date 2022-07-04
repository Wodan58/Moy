/*
    module  : setsize.c
    version : 1.12
    date    : 06/20/22
*/
#ifndef SETSIZE_C
#define SETSIZE_C

/**
setsize  :  ->  setsize
Pushes the maximum number of elements in a set (platform dependent).
Typically it is 32, and set members are in the range 0..31.
*/
PRIVATE void do_setsize(pEnv env)
{
    PUSH_NUM(INTEGER_, SETSIZE_);
}
#endif
