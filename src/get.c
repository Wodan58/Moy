/*
    module  : get.c
    version : 1.7
    date    : 07/02/18
*/

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
