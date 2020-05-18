/*
    module  : get.c
    version : 1.11
    date    : 03/28/20
*/
#ifndef GET_C
#define GET_C

/**
get  :  ->  F
Reads a factor from input and pushes it onto stack.
*/
PRIVATE void do_get(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    readfactor(yylex());
}
#endif
