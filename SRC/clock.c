/*
    module  : clock.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
clock  :  ->  I
Pushes the integer value of current CPU usage in milliseconds.
*/
/* clock.c */
PUSH_PROC(clock_, INTEGER_, clock() - startclock)
