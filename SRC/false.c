/*
    module  : false.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
false  :  ->  false
Pushes the value false.
*/
PRIVATE void do_false(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(BOOLEAN_, 0);
}
