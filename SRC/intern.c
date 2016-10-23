/*
    module  : intern.c
    version : 1.5
    date    : 10/21/16
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
    int i;

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
    for (i = 0; optable[i].name; i++)
	if (!strcmp(id, optable[i].name)) {
	    if (OUTSIDE) {
		stk->op = ANON_FUNCT_;
		stk->u.proc = optable[i].proc;
	    } else
		UNARY(ANON_FUNCT_NEWNODE, optable[i].proc);
	    return;
	}
    HashValue(id);
    lookup();
    if (OUTSIDE) {
	stk->u.ent = location;
	stk->op = USR_;
    } else
	UNARY(USR_NEWNODE, location);
}
