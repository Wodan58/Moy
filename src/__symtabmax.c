/*
    module  : __symtabmax.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
__symtabmax  :  ->  I
Pushes value of maximum size of the symbol table.
*/
PRIVATE void do___symtabmax(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
#endif
    PUSH(INTEGER_, SYMTABMAX);
}
