/*
    module  : getch.c
    version : 1.6
    date    : 07/02/18
*/

/**
getch  :  ->  N
Reads a character from input and puts it onto stack.
*/
PRIVATE void do_getch(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(CHAR_, getchar());
}
