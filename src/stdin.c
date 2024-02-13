/*
    module  : stdin.c
    version : 1.8
    date    : 02/01/24
*/
#ifndef STDIN_C
#define STDIN_C

/**
IMMEDIATE  1170  stdin  :  A	->  S
[FOREIGN] Pushes the standard input stream.
*/
void stdin_(pEnv env)
{
    Node node;

    node.u.fil = stdin;
    node.op = FILE_;
    env->stck = pvec_add(env->stck, node);
}
#endif
