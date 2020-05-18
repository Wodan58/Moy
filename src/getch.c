/*
    module  : getch.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef GETCH_C
#define GETCH_C

/**
getch  :  ->  N
Reads a character from input and puts it onto stack.
*/
PRIVATE void do_getch(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(CHAR_, getchar());
}
#endif
