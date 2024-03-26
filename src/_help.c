/*
    module  : _help.c
    version : 1.10
    date    : 03/21/24
*/
#ifndef _HELP_C
#define _HELP_C

/**
Q0  IGNORE_OK  2910  _help  :  N  ->
[IMPURE] Lists all hidden symbols in library and then all hidden builtin
symbols.
*/
void _help_(pEnv env)
{
    Entry ent;
    int name_length, column = 0, i = vec_size(env->symtab);

    while (i) {
	ent = vec_at(env->symtab, --i);
	if (strchr("#_", ent.name[0])) {
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
