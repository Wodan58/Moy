/*
    module  : undefs.c
    version : 1.14
    date    : 06/20/22
*/
#ifndef UNDEFS_C
#define UNDEFS_C

/**
undefs  :  ->  [..]
Push a list of all undefined symbols in the current symbol table.
*/
PRIVATE void do_undefs(pEnv env)
{
#ifdef COMPILING
    int i;
    Node node;
    char *ptr;
    Node *root = 0;

    COMPILE;
    for (i = dict_size(env) - 1; i >= 0; i--) {
	node.u.num = i;
	ptr = dict_descr(env, &node);
	if (*ptr && *ptr != '_' && !dict_body(env, i))
	    root = STRING_NEWNODE(ptr, root);
    }
    PUSH_PTR(LIST_, root);
#endif
}
#endif
