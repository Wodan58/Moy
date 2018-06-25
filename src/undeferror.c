/*
    module  : undeferror.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
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
