/*
    module  : argv.c
    version : 1.7
    date    : 07/02/18
*/

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
