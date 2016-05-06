/*
    module  : stderr.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
stderr  :  ->  S
Pushes the standard error stream.
*/
/* stderr.c */
PUSH_PROC(stderr_, FILE_, stderr)
