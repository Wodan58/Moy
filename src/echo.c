/*
    module  : echo.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
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
