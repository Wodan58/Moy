/*
    module  : rand.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
rand  :  ->  I
I is a random integer.
*/
PRIVATE void do_rand(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, rand());
}
