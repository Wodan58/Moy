/*
    module  : quit.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
quit  ->
Exit from Joy.
*/
PRIVATE void do_quit(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    exit(0);
}
