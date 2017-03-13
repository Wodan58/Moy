/*
    module  : nothing.c
    version : 1.1
    date    : 03/12/17
*/
#include "runtime.h"

/*
nothing  :  ->  nothing
Pushes the value nothing.
*/
PRIVATE void do_nothing(void)
{
    Node temp;

#ifndef NCHECK
    COMPILE;
#endif
    temp.u.num = temp.op = DO_NOTHING;
    DUPLICATE(&temp);
}
