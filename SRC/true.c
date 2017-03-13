/*
    module  : true.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
true  :  ->  true
Pushes the value true.
*/
PRIVATE void do_true(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(BOOLEAN_, 1);
}
