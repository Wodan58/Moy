/*
    module  : __symtabmax.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef __SYMTABMAX_X
#define __SYMTABMAX_C

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
#endif
