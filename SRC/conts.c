/*
    module  : conts.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
conts  ->  [[P] [Q] ..]
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
