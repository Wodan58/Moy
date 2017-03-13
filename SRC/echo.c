/*
    module  : echo.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
echo  :  ->  I
Pushes value of echo flag, I = 0..3.
*/
PRIVATE void do_echo(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, echoflag);
}
