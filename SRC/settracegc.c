/*
    module  : settracegc.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
__settracegc  :  I  ->
Sets value of flag for tracing garbage collection to I (= 0..2).
*/
/* settracegc.c */
USETOP(__settracegc_, "settracegc", NUMERICTYPE, tracegc = stk->u.num)
