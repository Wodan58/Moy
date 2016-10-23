/*
    module  : argv.c
    version : 1.3
    date    : 10/04/16
*/
#include "interp.h"

/*
argv  :  ->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
/* argv.c */
PRIVATE void argv_(void)
{
    int i;
    Node *cur = 0;

    for (i = g_argc - 1; i >= 0; i--)
	cur = heapnode(STRING_, g_argv[i], cur);
    PUSH(LIST_, cur);
}
