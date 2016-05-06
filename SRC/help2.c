/*
    module  : help2.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
_help  :  ->
Lists all hidden symbols in library and then all hidden builtin symbols.
*/
/* help2.c */
#define PROCEDURE	_help_
#define REL		==
#include "help.c"
