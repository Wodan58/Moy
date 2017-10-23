/*
    module  : help2.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
_help  :  ->
Lists all hidden symbols in library and then all hidden builtin symbols.
*/
#define PROCEDURE	do_help1
#define REL		==
#include "help.c"
