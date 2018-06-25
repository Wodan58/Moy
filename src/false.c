/*
    module  : false.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
false  :  ->  false
Pushes the value false.
*/
PRIVATE void do_false(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(BOOLEAN_);
    COMPILE;
#endif
    PUSH(BOOLEAN_, 0);
}
