/*
    module  : dup.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
dup  :  X  ->  X X
Pushes an extra copy of X onto stack.
*/
/* dup.c */
PRIVATE void dup_(void)
{
    ONEPARAM("dup");
    DUPLICATE(stk);
}
