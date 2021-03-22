/*
    module  : intern.c
    version : 1.15
    date    : 03/15/21
*/
#ifndef INTERN_C
#define INTERN_C

/**
intern  :  "sym"  ->  sym
Pushes the item whose name is "sym".
*/
PRIVATE void do_intern(pEnv env)
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
    strncpy(id, env->stk->u.str, ALEN);
    id[ALEN - 1] = 0;
    if (id[0] == '-' || !strchr("(#)[]{}.;'\"0123456789", id[0]))
	for (ptr = id + 1; *ptr; ptr++)
	    if (!isalnum((int) *ptr) && !strchr("=_-", *ptr))
		break;
#ifndef NCHECK
    if (!ptr || *ptr)
	execerror("valid name", id);
#endif
    i = lookup(env, id);
    if (dict_flags(env, i) & IS_BUILTIN) {
	env->stk->op = ANON_FUNCT_;
	env->stk->u.proc = (proc_t)dict_body(env, i);
    } else {
	env->stk->op = USR_;
	env->stk->u.num = i;
    }
#endif
}
#endif
