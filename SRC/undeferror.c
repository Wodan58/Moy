/*
    module  : undeferror.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
undeferror  :  ->  I
Pushes current value of undefined-is-error flag.
*/
/* undeferror.c */
PUSH_PROC(undeferror_, INTEGER_, undeferror)
