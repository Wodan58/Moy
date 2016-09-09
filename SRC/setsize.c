/*
    module  : setsize.c
    version : 1.3
    date    : 09/09/16
*/
#include "interp.h"

/*
setsize  :  ->  setsize
Pushes the maximum number of elements in a set (platform dependent).
Typically it is 32, and set members are in the range 0..31.
*/
/* setsize.c */
PUSH_PROC(setsize_, INTEGER_, _SETSIZE_)
