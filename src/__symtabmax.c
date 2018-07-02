/*
    module  : __symtabmax.c
    version : 1.6
    date    : 07/02/18
*/

/**
__symtabmax  :  ->  I
Pushes value of maximum size of the symbol table.
*/
PRIVATE void do___symtabmax(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, SYMTABMAX);
}
