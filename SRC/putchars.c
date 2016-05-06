/*
    module  : putchars.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
putchars  :  "abc.."  ->
Writes abc.. (without quotes)
*/
/* putchars.c */
USETOP(putchars_, "putchars", STRING, printf("%s", stk->u.str))
