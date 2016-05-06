/*
    module  : putch.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
/* putch.c */
USETOP(putch_, "putch", NUMERICTYPE, printf("%c", (int) stk->u.num))
