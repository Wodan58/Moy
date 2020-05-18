/*
    module  : intern.c
    version : 1.14
    date    : 03/28/20
*/
#ifndef INTERN_C
#define INTERN_C

/**
intern  :  "sym"  ->  sym
Pushes the item whose name is "sym".
*/
PRIVATE void do_intern(void)
{
#ifndef OLD_RUNTIME
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
#ifndef NCHECK
    if (!ptr || *ptr)
	execerror("valid name", id);
#endif
    i = lookup(id);
    if (dict_flags(i) & IS_BUILTIN) {
	stk->op = ANON_FUNCT_;
	stk->u.proc = (proc_t)dict_body(i);
    } else {
	stk->op = USR_;
	stk->u.num = i;
    }
#endif
}
#endif
