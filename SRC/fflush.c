/*
    module  : fflush.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fflush  :  S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
/* fflush.c */
PRIVATE void fflush_(void)
{
    ONEPARAM("fflush");
    FILE("fflush");
    fflush(stk->u.fil);
}
