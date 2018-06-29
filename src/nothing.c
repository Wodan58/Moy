/*
    module  : nothing.c
    version : 1.4
    date    : 06/29/18
*/
#include "runtime.h"

/**
nothing  :  ->  nothing
Pushes the value nothing.
*/
PRIVATE void do_nothing(void)
{
    Node temp;

#ifndef NCHECK
    if (optimizing)
	add_history(Nothing);
    COMPILE;
#endif
    temp.u.num = temp.op = Nothing;
    DUPLICATE(&temp);
}
