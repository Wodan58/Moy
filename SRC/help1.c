/*
    module  : help1.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
help  :  ->
Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
/* help1.c */
#define PROCEDURE	help_
#define REL		!=
#include "help.c"
