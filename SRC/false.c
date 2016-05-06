/*
    module  : false.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
false  :  ->  false
Pushes the value false.
*/
/* false.c */
PUSH_PROC(false_, BOOLEAN_, 0)
