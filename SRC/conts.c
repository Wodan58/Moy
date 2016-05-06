/*
    module  : conts.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
conts  ->  [[P] [Q] ..]
Pushes current continuations. Buggy, do not use.
*/
/* conts.c */
PUSH_PROC(conts_, LIST_, 0)
