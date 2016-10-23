/*
    module  : undefs.c
    version : 1.3
    date    : 10/04/16
*/
#include "interp.h"

/*
undefs  :  ->  [..]
Push a list of all undefined symbols in the current symbol table.
*/
/* undefs.c */
PRIVATE void undefs_(void)
{
    Node *n = 0;
    Entry *i = symtabindex;

    while (--i != symtab)
	if (i->name[0] && i->name[0] != '_' && !i->u.body)
	    n = heapnode(STRING_, i->name, n);
    PUSH(LIST_, n);
}
