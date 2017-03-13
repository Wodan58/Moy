/*
    module  : argc.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
argc  :  ->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
PRIVATE void do_argc(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, g_argc);
}
