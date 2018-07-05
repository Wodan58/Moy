/*
    module  : intern.c
    version : 1.11
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_intern(void)
{
    char *name;
    proc_t proc;

    name = (char *)stk[-1];
    proc = nameproc(name);
    stk[-1] = (node_t)proc;
}
#else
/**
intern  :  "sym"  ->  sym
Pushes the item whose name is "sym".
*/
PRIVATE void do_intern(void)
{
#ifndef NCHECK
    int i;
    char id[ALEN];
    char *ptr = 0;

    if (compiling && STRING_1)
	;
    else
	COMPILE;
    ONEPARAM("intern");
    STRING("intern");
    strncpy(id, stk->u.str, ALEN);
    id[ALEN - 1] = 0;
    if (id[0] == '-' || !strchr("(#)[]{}.;'\"0123456789", id[0]))
	for (ptr = id + 1; *ptr; ptr++)
	    if (!isalnum((int) *ptr) && !strchr("=_-", *ptr))
		break;
    if (!ptr || *ptr)
	execerror("valid name", id);
    i = lookup(id);
    if (OUTSIDE) {
	if (dict_flags(i) & IS_BUILTIN) {
	    stk->op = ANON_FUNCT_;
	    stk->u.proc = (proc_t)dict_body(i);
	} else {
	    stk->op = USR_;
	    stk->u.num = i;
	}
    } else if (dict_flags(i) & IS_BUILTIN)
	UNARY(ANON_FUNCT_NEWNODE, (proc_t)dict_body(i));
    else
	UNARY(USR_NEWNODE, i);
#endif
}
#endif
