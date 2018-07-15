/*
    module  : help.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef HELP_X
#define HELP_C

#ifdef NEW_RUNTIME
void do_help(void)
{
    TRACE;
}
#else
/**
help  :  ->
Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
#define PROCEDURE	do_help
#define REL		!=
#include "help.h"
#endif
#endif
