/*
    module  : setundeferror.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
setundeferror  :  I  ->
Sets flag that controls behavior of undefined functions
(0 = no error, 1 = error).
*/
/* setundeferror.c */
USETOP(setundeferror_, "setundeferror", NUMERICTYPE, undeferror = stk->u.num)
