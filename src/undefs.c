/*
    module  : undefs.c
    version : 1.12
    date    : 03/28/20
*/
#ifndef UNDEFS_C
#define UNDEFS_C

/**
undefs  :  ->  [..]
Push a list of all undefined symbols in the current symbol table.
*/
PRIVATE void do_undefs(void)
{
#ifndef OLD_RUNTIME
    int i;
    char *ptr;
    Node *root = 0;

    COMPILE;
    for (i = dict_size() - 1; i >= 0; i--) {
	ptr = dict_descr(i);
	if (*ptr && *ptr != '_' && !dict_body(i))
	    root = newnode(STRING_, ptr, root);
    }
    PUSH(LIST_, root);
#endif
}
#endif
