/*
    module  : argv.c
    version : 1.8
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_argv(void)
{
    int i;
    code_t *root = 0, *cur;

    TRACE;
    for (i = g_argc - 1; i >= 0; i--) {
	cur = joy_code();
	cur->str = g_argv[i];
	cur->next = root;
	root = cur;
    }
    do_push((node_t)root);
}
#else
/**
argv  :  ->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
PRIVATE void do_argv(void)
{
    int i;
    Node *cur = 0;

#ifndef NCHECK
    COMPILE;
#endif
    for (i = g_argc - 1; i >= 0; i--)
	cur = heapnode(STRING_, (void *)g_argv[i], cur);
    PUSH(LIST_, cur);
}
#endif
