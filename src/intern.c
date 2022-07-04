/*
    module  : intern.c
    version : 1.16
    date    : 06/20/22
*/
#ifndef INTERN_C
#define INTERN_C

/**
intern  :  "sym"  ->  sym
Pushes the item whose name is "sym".
*/
PRIVATE void do_intern(pEnv env)
{
#ifdef COMPILING
    int i;
    char id[ALEN], *ptr = 0;

    ONEPARAM("intern");
    STRING("intern");
    strncpy(id, env->stk->u.str, ALEN);
    id[ALEN - 1] = 0;
    if (!strchr("\"#'().0123456789;[]{}", id[0])) {
        if (id[0] == '-' && isdigit((int)id[1]))
            ;
        else
	    for (ptr = id + 1; *ptr; ptr++)
	        if (!isalnum((int) *ptr) && !strchr("=_-", *ptr))
		    break;
    }
    CHECKNAME(ptr, "intern");
    i = lookup(env, id);
    if (dict_flags(env, i) & IS_BUILTIN)
	UNARY(ANON_FUNCT_NEWNODE, (proc_t)dict_body(env, i));
    else
	UNARY(USR_NEWNODE, i);
#endif
}
#endif
