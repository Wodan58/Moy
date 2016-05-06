/*
    module  : autoput.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
autoput  :  ->  I
Pushes current value of flag for automatic output, I = 0..2.
*/
/* autoput.c */
PUSH_PROC(autoput_, INTEGER_, autoput)
