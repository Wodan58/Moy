/*
    module  : echo.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
echo  :  ->  I
Pushes value of echo flag, I = 0..3.
*/
PRIVATE void do_echo(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, echoflag);
}
