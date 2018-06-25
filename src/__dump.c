/*
    module  : __dump.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
__dump  :  ->  [..]
debugging only: pushes the dump as a list.
*/
PRIVATE void do___dump(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(LIST_);
    COMPILE;
#endif
    PUSH(LIST_, 0);
}
