/*
    module  : get.c
    version : 1.8
    date    : 07/05/18
*/
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
