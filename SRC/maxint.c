/*
    module  : maxint.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
maxint  :  ->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
/* maxint.c */
PUSH_PROC(maxint_, INTEGER_, MAXINT)
