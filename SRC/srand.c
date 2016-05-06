/*
    module  : srand.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
srand  :  I  ->
Sets the random integer seed to integer I.
*/
/* srand.c */
USETOP(srand_, "srand", INTEGER, srand(stk->u.num))
