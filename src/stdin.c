/*
    module  : stdin.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef STDIN_C
#define STDIN_C

/**
OK 1170  stdin  :  A	->  S
Pushes the standard input stream.
*/
void stdin_(pEnv env)
{
    Node node;

    node.u.fil = stdin;
    node.op = FILE_;
    env->stck = pvec_add(env->stck, node);
}
#endif
