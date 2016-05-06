/*
    module  : stdout.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
stdout  :  ->  S
Pushes the standard output stream.
*/
/* stdout.c */
PUSH_PROC(stdout_, FILE_, stdout)
