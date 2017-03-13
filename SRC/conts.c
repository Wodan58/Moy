/*
    module  : conts.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
conts  ->  [[P] [Q] ..]
Pushes current continuations. Buggy, do not use.
*/
PRIVATE void do_conts(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(LIST_, 0);
}
