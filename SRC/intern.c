/*
    module  : intern.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
intern  :  "sym"  ->  sym
Pushes the item whose name is "sym".
*/
/* intern.c */
PRIVATE void intern_(void)
{
#ifdef RUNTIME_CHECKS
    char *ptr = 0;
#endif

    ONEPARAM("intern");
    STRING("intern");
    strncpy(id, stk->u.str, ALEN);
    id[ALEN - 1] = 0;
#ifdef RUNTIME_CHECKS
    if (id[0] == '-' || !strchr("(#)[]{}.;'\"0123456789", id[0]))
	for (ptr = id + 1; *ptr; ptr++)
	    if (!isalnum((int) *ptr) && !strchr("=_-", *ptr))
		break;
    if (!ptr || *ptr)
	execerror("valid name", id);
#endif
    HashValue(id);
    lookup();
    if (OUTSIDE) {
	if (location < firstlibra) {
	    stk->u.proc = location->u.proc;
	    stk->op = location - symtab;
	} else {
	    stk->u.ent = location;
	    stk->op = USR_;
	}
    } else if (location < firstlibra)
	GUNARY(location - symtab, location->u.proc);
    else
	UNARY(USR_NEWNODE, location);
}
