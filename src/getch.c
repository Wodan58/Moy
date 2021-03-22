/*
    module  : getch.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef GETCH_C
#define GETCH_C

/**
getch  :  ->  N
Reads a character from input and puts it onto stack.
*/
PRIVATE void do_getch(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH_NUM(CHAR_, getchar());
}
#endif
