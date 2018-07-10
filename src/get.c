/*
    module  : get.c
    version : 1.9
    date    : 07/10/18
*/
#ifndef GET_X
#define GET_C

#ifdef RUNTIME
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
#ifndef NCHECK
    COMPILE;
#endif
    readfactor(yylex());
}
#endif
#endif
