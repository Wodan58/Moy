/*
    module  : argc.c
    version : 1.4
    date    : 04/08/17
*/
#include "runtime.h"

/*
argc  :  ->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
PRIVATE void do_argc(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, g_argc);
}
