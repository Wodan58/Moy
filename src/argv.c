/*
    module  : argv.c
    version : 1.14
    date    : 06/20/22
*/
#ifndef ARGV_C
#define ARGV_C

/**
argv  :  ->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
PRIVATE void do_argv(pEnv env)
{
    int i;
    Node *cur = 0;

    COMPILE;
    for (i = g_argc - 1; i >= 0; i--)
	cur = STRING_NEWNODE(g_argv[i], cur);
    PUSH_PTR(LIST_, cur);
}
#endif
