/*
    module  : autoput.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
autoput  :  ->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
PRIVATE void do_autoput(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, autoput);
}
