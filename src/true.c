/*
    module  : true.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
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
