/*
    module  : getch.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
getch  :  ->  N
Reads a character from input and puts it onto stack.
*/
PRIVATE void do_getch(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(CHAR_);
    COMPILE;
#endif
    PUSH(CHAR_, getchar());
}
