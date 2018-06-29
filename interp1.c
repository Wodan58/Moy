/*
    module  : interp1.c
    version : 1.3
    date    : 06/29/18
*/
#define NCHECK
#define RUNTIME
#include "runtime.h"
#include "interp.c"

/*
 * dict_descr used in writefactor
 */
char *dict_descr(int index)
{
    return "unknown";
}

char *dict_name(int index)
{
    return "unknown";
}

/*
 * init_dict used in initsym
 */
void init_dict(void)
{
}
