/*
    module  : getch.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef GETCH_X
#define GETCH_C

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
#endif
