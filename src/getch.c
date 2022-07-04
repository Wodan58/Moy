/*
    module  : getch.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef GETCH_C
#define GETCH_C

/**
getch  :  ->  N
Reads a character from input and puts it onto stack.
*/
PRIVATE void do_getch(pEnv env)
{
    COMPILE;
    PUSH_NUM(CHAR_, getnextchar());
}
#endif
