/*
    module  : conts.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
conts  :  ->  [[P] [Q] ..]
Pushes current continuations. Buggy, do not use.
*/
PRIVATE void do_conts(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history2(LIST_, LIST_);
    COMPILE;
#endif
    PUSH(LIST_, 0);
}
