/*
    module  : quit.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
quit  :  ->
Exit from Joy.
*/
PRIVATE void do_quit(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    exit(0);
}
