/*
    module  : argv.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef ARGV_C
#define ARGV_C

/**
OK 3040  argv  :  A	->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
PRIVATE void argv_(pEnv env)
{
#ifndef COMPILER
    int i;
    Node node, elem;

    lst_init(node.u.lis);
    elem.op = STRING_;
    for (i = env->g_argc - 1; i >= 0; i--) {
	elem.u.str = env->g_argv[i];
	lst_push(node.u.lis, elem);
    }
    node.op = LIST_;
    lst_push(env->stck, node);
#endif
}
#endif
