/*
    module  : help.c
    version : 1.5
    date    : 07/10/18
*/
#ifndef HELP_X
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
#endif
