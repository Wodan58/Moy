/*
    module  : argv.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
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
