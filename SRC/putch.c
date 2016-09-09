/*
    module  : putch.c
    version : 1.2
    date    : 09/09/16
*/
#include "interp.h"

/*
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
/* putch.c */
USETOP(putch_, "putch", NUMERICTYPE, (writeline = stk->u.num == '\n', printf("%c", (int) stk->u.num)))
