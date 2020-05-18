/*
    module  : argv.c
    version : 1.12
    date    : 03/28/20
*/
#ifndef ARGV_C
#define ARGV_C

/**
argv  :  ->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
PRIVATE void do_argv(void)
{
    int i;
    Node *cur = 0;

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    for (i = g_argc - 1; i >= 0; i--)
	cur = newnode(STRING_, (void *)g_argv[i], cur);
    PUSH(LIST_, cur);
}
#endif
