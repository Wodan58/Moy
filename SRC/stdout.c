/*
    module  : stdout.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
stdout  :  ->  S
Pushes the standard output stream.
*/
PRIVATE void do_stdout(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(FILE_, stdout);
}
