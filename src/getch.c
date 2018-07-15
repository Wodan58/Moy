/*
    module  : getch.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef GETCH_X
#define GETCH_C

#ifdef NEW_RUNTIME
void do_getch(void)
{
    TRACE;
    do_push(getchar());
}
#else
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
#endif
