/*
    module  : help.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef HELP_C
#define HELP_C

/**
OK 2920  help  :  N	->
Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
void help_(pEnv env)
{
    Entry ent;
    int name_length, column = 0, i = sym_size(env->symtab);

    while (i) {
        ent = sym_at(env->symtab, --i);
        if (!strchr("(0123456789_", ent.name[0])) {
            name_length = strlen(ent.name) + 1;
            if (column + name_length > 72) {
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
