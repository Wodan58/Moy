/*
    module  : __symtabmax.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef __SYMTABMAX_C
#define __SYMTABMAX_C

/**
__symtabmax  :  ->  I
Pushes value of maximum size of the symbol table.
*/
PRIVATE void do___symtabmax(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    PUSH(INTEGER_, symtabmax());
}
#endif
