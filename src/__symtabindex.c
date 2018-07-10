/*
    module  : __symtabindex.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef __SYMTABINDEX_X
#define __SYMTABINDEX_C

/**
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
PRIVATE void do___symtabindex(void)
{
#ifndef NCHECK
    COMPILE;
    PUSH(INTEGER_, dict_size() - 1);
#endif
}
#endif
