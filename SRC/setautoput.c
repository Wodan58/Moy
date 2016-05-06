/*
    module  : setautoput.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
setautoput  :  I  ->
Sets value of flag for automatic put to I (if I = 0, none;
if I = 1, put; if I = 2, stack).
*/
/* setautoput.c */
USETOP(setautoput_, "setautoput", NUMERICTYPE, autoput = stk->u.num)
