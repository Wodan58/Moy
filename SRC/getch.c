/*
    module  : getch.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
getch  :  ->  N
Reads a character from input and puts it onto stack.
*/
/* getch.c */
PUSH_PROC(getch_, CHAR_, getchar())
