/*
    module  : help.c
    version : 1.7
    date    : 03/28/20
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
#endif
