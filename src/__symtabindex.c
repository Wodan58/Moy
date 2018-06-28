/*
    module  : __symtabindex.c
    version : 1.6
    date    : 06/28/18
*/
#include "runtime.h"

/**
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
PRIVATE void do___symtabindex(void)
{
#ifndef NCHECK
    if (optimizing)
	add_history(INTEGER_);
    COMPILE;
    PUSH(INTEGER_, dict_size() - 1);
#endif
}
