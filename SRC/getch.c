/*
    module  : getch.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
getch  :  ->  N
Reads a character from input and puts it onto stack.
*/
PRIVATE void do_getch(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, getchar());
}
