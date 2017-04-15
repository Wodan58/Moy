/*
    module  : autoput.c
    version : 1.4
    date    : 04/08/17
*/
#include "runtime.h"

/*
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
