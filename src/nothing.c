/*
    module  : nothing.c
    version : 1.2
    date    : 04/09/17
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
    if (optimizing)
	add_history(DO_NOTHING);
    COMPILE;
#endif
    temp.u.num = temp.op = DO_NOTHING;
    DUPLICATE(&temp);
}
