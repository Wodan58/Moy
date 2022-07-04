/*
    module  : runtime.c
    version : 1.7
    date    : 06/17/22
*/
#include "runtime.h"

YYSTYPE yylval;		/* copy */

/*
 * lookup is used in readfactor. The task is to locate the string in the symbol
 * table and to return the index in the symbol table.
 */
int lookup(pEnv env, char *str)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (!strcmp(str, table[i].name))
	    break;
    return i;
}

/*
 * nameproc - translate name to function address, currently not used.
 */
proc_t nameproc(char *name)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (!strcmp(name, table[i].name))
	    break;
    return table[i].proc;
}

/*
 * procname - translate function address to symbol name, used in writefactor.
 */
char *procname(proc_t proc)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (proc == table[i].proc)
	    break;
    return table[i].name;
}

/*
 * dict_descr is used in writefactor.
 */
char *dict_descr(pEnv env, Node *node)
{
    char *name;

    name = procname(node->u.proc);
    if (*name)
	return name;
    return node->u.str;
}

/*
 * nickname - translate function address to symbol name, except that the
 *	      nickname is used instead of the normal name, used in compare.h
 */
char *nickname(proc_t proc)
{
    int i, ch;
    char *ptr;

    for (i = 0; table[i].proc; i++)
	if (proc == table[i].proc)
	    break;
    ptr = table[i].name;
    ch = *ptr;
    if (!ch || isalnum(ch) || ch == '_')
	return ptr;
    while (*ptr)
	ptr++;
    return ptr + 1;
}

/*
 * dump the symbol table, used in initsym.c
 */
void dump_table(pEnv env)
{
    int i;

    for (i = 0; table[i].proc; i++)
	printf("%s\n", table[i].name);
}
