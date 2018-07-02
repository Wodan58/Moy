/*
    module  : __symtabindex.c
    version : 1.7
    date    : 07/02/18
*/

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
