/*
    module  : runtime.c
    version : 1.3
    date    : 03/15/21
*/
#include "runtime.h"

/*
 * initialise the compiler
 */
void initialise(void)
{
}

/*
 * finalize the compiled program
 */
void finalise(pEnv env)
{
}

/*
 * init_dict used in initsym
 */
void init_dict(pEnv env)
{
}
/*
 * dict_descr used in writefactor
 */
char *dict_descr(pEnv env, int index)
{
    return "unknown";
}

/*
 * lookup is replaced by procname/nameproc
 */
int lookup(pEnv env, char *str)
{
    return 0;
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
