/*
    module  : inisym.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/* inisym.c */
PUBLIC void inisymboltable(void)
{				/* initialise */
    int i;
    char *s;

    symtabindex = symtab;
    for (i = 0; i < HASHSIZE; hashentry[i++] = symtab);
    for (i = 0; optable[i].name; i++) {
	s = optable[i].name;
	HashValue(s);
	symtabindex->name = optable[i].name;
	symtabindex->u.proc = optable[i].proc;
	symtabindex->next = hashentry[hashvalue];
	hashentry[hashvalue] = symtabindex;
	symtabindex++;
    }
    firstlibra = symtabindex;
}
