/*
    module  : symtabmax.c
    version : 1.4
    date    : 04/09/17
*/
#include "runtime.h"

/*
__symtabmax  :  ->  I
Pushes value of maximum size of the symbol table.
*/
PRIVATE void do_symtabmax(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, SYMTABMAX);
}
