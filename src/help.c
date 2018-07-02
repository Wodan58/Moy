/*
    module  : help.c
    version : 1.4
    date    : 07/02/18
*/

/**
help  :  ->
Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
#define PROCEDURE	do_help
#define REL		!=
#include "help.h"
