/*
    module  : argv.c
    version : 1.6
    date    : 06/25/18
*/
#include "runtime.h"

/**
argv  :  ->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
PRIVATE void do_argv(void)
{
    int i;
    Node *cur = 0;

#ifndef NCHECK
    if (optimizing)
	add_history2(LIST_, STRING_);
    COMPILE;
#endif
    for (i = g_argc - 1; i >= 0; i--)
	cur = heapnode(STRING_, (void *)g_argv[i], cur);
    PUSH(LIST_, cur);
}
