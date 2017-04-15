/*
    module  : undeferror.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
undeferror  :  ->  I
Pushes current value of undefined-is-error flag.
*/
PRIVATE void do_undeferror(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, undeferror);
}
