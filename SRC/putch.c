/*
    module  : putch.c
    version : 1.3
    date    : 10/19/16
*/
#include "interp.h"

/*
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
/* putch.c */
USETOP(putch_, "putch", NUMERICTYPE, printf("%c", (int) stk->u.num))
