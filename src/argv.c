/*
    module  : argv.c
    version : 1.13
    date    : 03/15/21
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

#ifndef OLD_RUNTIME
    COMPILE;
#endif
    for (i = g_argc - 1; i >= 0; i--)
	cur = STRING_NEWNODE(g_argv[i], cur);
    PUSH_PTR(LIST_, cur);
}
#endif
