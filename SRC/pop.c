/*
    module  : pop.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
pop  :  X  ->
Removes X from top of the stack.
*/
/* pop.c */
PRIVATE void pop_(void)
{
    ONEPARAM("pop");
    POP(stk);
}
