/*
    module  : interp1.c
    version : 1.5
    date    : 07/07/18
*/
#define NCHECK
#include "runtime.h"
#include "interp.c"

/*
 * dict_descr used in writefactor and interprete
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

char *procname(proc_t proc)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (proc == table[i].proc)
	    return table[i].name;
    return 0;
}

proc_t nameproc(char *name)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (!strcmp(name, table[i].name))
	    return table[i].proc;
    return 0;
}
