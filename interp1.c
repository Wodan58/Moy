/*
    module  : interp1.c
    version : 1.7
    date    : 05/30/19
*/
#define OLD_RUNTIME
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
	    break;
    return table[i].name;
}

proc_t nameproc(char *name)
{
    int i;

    for (i = 0; table[i].proc; i++)
	if (!strcmp(name, table[i].name))
	    break;
    return table[i].proc;
}
