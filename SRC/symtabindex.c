/*
    module  : symtabindex.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
__symtabindex  :  ->  I
Pushes current size of the symbol table.
*/
/* symtabindex.c */
PUSH_PROC(__symtabindex_, INTEGER_, symtabindex - symtab)
