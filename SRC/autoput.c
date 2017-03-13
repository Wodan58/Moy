/*
    module  : autoput.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
autoput  :  ->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
PRIVATE void do_autoput(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, autoput);
}
