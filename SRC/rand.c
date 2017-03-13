/*
    module  : rand.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
rand  :  ->  I
I is a random integer.
*/
PRIVATE void do_rand(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, rand());
}
