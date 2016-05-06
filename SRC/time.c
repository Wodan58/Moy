/*
    module  : time.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
time  :  ->  I
Pushes the current time (in seconds since the Epoch).
*/
/* time.c */
PUSH_PROC(time_, INTEGER_, time(0))
