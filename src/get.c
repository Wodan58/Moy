/*
    module  : get.c
    version : 1.10
    date    : 07/15/18
*/
#ifndef GET_X
#define GET_C

#ifdef NEW_RUNTIME
void do_get(void)
{
    TRACE;
    readfactor(yylex());
}
#else
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
#endif
