/*
    module  : help.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
help  :  ->
Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
#define PROCEDURE	do_help
#define REL		!=
#include "help.h"
