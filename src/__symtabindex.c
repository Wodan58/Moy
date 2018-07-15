/*
    module  : __symtabindex.c
    version : 1.9
    date    : 07/15/18
*/
#ifndef __SYMTABINDEX_X
#define __SYMTABINDEX_C

#ifdef NEW_RUNTIME
void do___symtabindex(void)
{
    int i;

    TRACE;
    for (i = 0; table[i].proc; i++)
	;
    do_push(i);
}
#else
/**
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
PRIVATE void do___symtabindex(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
    PUSH(INTEGER_, symtabindex());
#endif
}
#endif
#endif
