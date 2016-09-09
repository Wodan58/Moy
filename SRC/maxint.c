/*
    module  : maxint.c
    version : 1.3
    date    : 09/09/16
*/
#include "interp.h"

/*
maxint  :  ->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
/* maxint.c */
PUSH_PROC(maxint_, INTEGER_, _MAXINT_)
