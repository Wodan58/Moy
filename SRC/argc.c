/*
    module  : argc.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
argc  :  ->  I
Pushes the number of command line arguments. This is quivalent to 'argv size'.
*/
/* argc.c */
PUSH_PROC(argc_, INTEGER_, g_argc)
