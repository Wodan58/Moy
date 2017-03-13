/*
    module  : setautoput.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
setautoput  :  I  ->
Sets value of flag for automatic put to I (if I = 0, none;
if I = 1, put; if I = 2, stack).
*/
PRIVATE void do_setautoput(void)
{
#ifndef NCHECK
    COMPILE;
    ONEPARAM("setautoput");
    NUMERICTYPE("setautoput");
#endif
    autoput = stk->u.num;
    POP(stk);
}
