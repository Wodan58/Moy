/*
    module  : help1.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
help  :  ->
Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
#define PROCEDURE	do_help
#define REL		!=
#include "help.c"
