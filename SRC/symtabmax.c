/*
    module  : symtabmax.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
__symtabmax  :  ->  I
Pushes value of maximum size of the symbol table.
*/
PRIVATE void do_symtabmax(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    PUSH(INTEGER_, SYMTABMAX);
}
