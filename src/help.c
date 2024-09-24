/*
    module  : help.c
    version : 1.11
    date    : 09/17/24
*/
#ifndef HELP_C
#define HELP_C

/**
Q0  IGNORE_OK  2900  help  :  N  ->
[IMPURE] Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
void help_(pEnv env)
{
    Entry ent;
    int name_length, column = 0, i = vec_size(env->symtab);

    while (i) {
	ent = vec_at(env->symtab, --i);
	if (!strchr("#0123456789_", ent.name[0])) {
	    name_length = strlen(ent.name) + 1;
	    if (column + name_length > HELPLINEMAX) {
		putchar('\n');
		column = 0;
	    }
	    printf("%s ", ent.name);
	    column += name_length;
	}
    }
    putchar('\n');
}
#endif
