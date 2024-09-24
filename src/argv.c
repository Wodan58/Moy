/*
    module  : argv.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef ARGV_C
#define ARGV_C

/**
Q0  OK  3040  argv  :  A  ->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
void argv_(pEnv env)
{
    int i;
    Node node, elem;

    vec_init(node.u.lis);
    elem.op = STRING_;
    for (i = env->g_argc - 1; i >= 0; i--) {
	elem.u.str = env->g_argv[i];
        vec_push(node.u.lis, elem);
    }
    node.op = LIST_;
    vec_push(env->stck, node);
}
#endif
