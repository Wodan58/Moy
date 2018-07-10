/*
    module  : undefs.c
    version : 1.9
    date    : 07/10/18
*/
#ifndef UNDEFS_X
#define UNDEFS_C

/**
undefs  :  ->  [..]
Push a list of all undefined symbols in the current symbol table.
*/
PRIVATE void do_undefs(void)
{
#ifndef NCHECK
    int i;
    char *ptr;
    Node *root = 0;

    COMPILE;
    for (i = dict_size() - 1; i >= 0; i--) {
	ptr = dict_descr(i);
	if (*ptr && *ptr != '_' && !dict_body(i))
	    root = heapnode(STRING_, ptr, root);
    }
    PUSH(LIST_, root);
#endif
}
#endif
