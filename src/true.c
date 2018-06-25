/*
    module  : true.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
true  :  ->  true
Pushes the value true.
*/
PRIVATE void do_true(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(BOOLEAN_);
    COMPILE;
#endif
    PUSH(BOOLEAN_, 1);
}
