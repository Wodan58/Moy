/*
    module  : runtime.c
    version : 1.1
    date    : 05/13/20
*/
#include "runtime.h"

YYSTYPE yylval;

/*
 * lookup is replaced by procname/nameproc
 */
int lookup(char *str)
{
    return 0;
}

/*
 * initialise the compiler
 */
void initialise(void)
{
}

/*
 * dict_descr used in writefactor
 */
char *dict_descr(int index)
{
    return "unknown";
}

/*
 * init_dict used in initsym
 */
void init_dict(void)
{
}

/*
 * translate function address to symbol name
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
 * translate symbol name to function address
 */
proc_t nameproc(char *name)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (!strcmp(name, table[i].name))
	    break;
    return table[i].proc;
}
