/*
    module  : false.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
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
