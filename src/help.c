/*
    module  : help.c
    version : 1.9
    date    : 06/20/22
*/
#ifndef HELP_C
#define HELP_C

/**
help  :  ->
Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
#define PROCEDURE	do_help
#define REL		!=
#include "help.h"
/* help.c */
#endif
