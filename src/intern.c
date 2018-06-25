/*
    module  : intern.c
    version : 1.8
    date    : 06/25/18
*/
#include "runtime.h"

/**
intern  :  "sym"  ->  sym
Pushes the item whose name is "sym".
*/
PRIVATE void do_intern(void)
{
    Entry *sym;
    char id[ALEN];
#ifndef NCHECK
    char *ptr = 0;

    if (optimizing)
	chg_history(USR_);
    if (optimizing && STRING_1)
	;
    else
	COMPILE;
    ONEPARAM("intern");
    STRING("intern");
#endif
    strncpy(id, stk->u.str, ALEN);
    id[ALEN - 1] = 0;
#ifndef NCHECK
    if (id[0] == '-' || !strchr("(#)[]{}.;'\"0123456789", id[0]))
	for (ptr = id + 1; *ptr; ptr++)
	    if (!isalnum((int) *ptr) && !strchr("=_-", *ptr))
		break;
    if (!ptr || *ptr)
	execerror("valid name", id);
#endif
    sym = lookup(id);
    if (OUTSIDE) {
	if (sym->flags & IS_BUILTIN) {
	    stk->op = ANON_FUNCT_;
	    stk->u.proc = sym->u.proc;
	} else {
	    stk->op = USR_;
	    stk->u.ent = sym;
	}
    } else if (sym->flags & IS_BUILTIN)
	UNARY(ANON_FUNCT_NEWNODE, sym->u.proc);
    else
	UNARY(USR_NEWNODE, sym);
}
