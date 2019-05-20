/*
    module  : undefs.c
    version : 1.11
    date    : 05/18/19
*/
#ifndef UNDEFS_X
#define UNDEFS_C

#ifdef NEW_RUNTIME
void do_undefs(void)
{
    TRACE;
}
#else
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
#endif
