/*
    module  : stderr.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
stderr  :  ->  S
Pushes the standard error stream.
*/
PRIVATE void do_stderr(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(FILE_, stderr);
}
