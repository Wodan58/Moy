/*
    module  : setsize.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
setsize  :  ->  setsize
Pushes the maximum number of elements in a set (platform dependent).
Typically it is 32, and set members are in the range 0..31.
*/
/* setsize.c */
PUSH_PROC(setsize_, INTEGER_, SETSIZE)
