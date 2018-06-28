/*
    module  : interp1.c
    version : 1.2
    date    : 06/28/18
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

/*
 * init_dict used in initsym
 */
void init_dict(void)
{
}
