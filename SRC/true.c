/*
    module  : true.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
true  :  ->  true
Pushes the value true.
*/
/* true.c */
PUSH_PROC(true_, BOOLEAN_, 1)
