/*
    module  : undefs.c
    version : 1.7
    date    : 06/28/18
*/
#include "runtime.h"

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

    if (optimizing)
	add_history2(LIST_, STRING_);
    COMPILE;
    for (i = dict_size() - 1; i >= 0; i--) {
	ptr = dict_descr(i);
	if (*ptr && *ptr != '_' &&
		(dict_flags(i) & (IS_MODULE | IS_BUILTIN)) == 0 &&
		!dict_body(i))
	    root = heapnode(STRING_, ptr, root);
    }
    PUSH(LIST_, root);
#endif
}
