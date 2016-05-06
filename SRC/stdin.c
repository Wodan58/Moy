/*
    module  : stdin.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
stdin  :  ->  S
Pushes the standard input stream.
*/
/* stdin.c */
PUSH_PROC(stdin_, FILE_, stdin)
