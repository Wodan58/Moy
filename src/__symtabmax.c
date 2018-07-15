/*
    module  : __symtabmax.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef __SYMTABMAX_X
#define __SYMTABMAX_C

#ifdef NEW_RUNTIME
void do___symtabmax(void)
{
    int i;

    TRACE;
    for (i = 0; table[i].proc; i++)
	;
    do_push(i);
}
#else
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
#endif
