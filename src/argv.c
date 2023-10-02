/*
    module  : argv.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef ARGV_C
#define ARGV_C

/**
OK 3040  argv  :  A	->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
PRIVATE void argv_(pEnv env)
{
    int i;
    Node node, elem;

    node.u.lis = pvec_init();
    elem.op = STRING_;
    for (i = env->g_argc - 1; i >= 0; i--) {
	elem.u.str = env->g_argv[i];
	node.u.lis = pvec_add(node.u.lis, elem);
    }
    node.op = LIST_;
    env->stck = pvec_add(env->stck, node);
}
#endif
