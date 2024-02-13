/*
    module  : stdout.c
    version : 1.8
    date    : 02/01/24
*/
#ifndef STDOUT_C
#define STDOUT_C

/**
IMMEDIATE  1180  stdout  :  A	->  S
[FOREIGN] Pushes the standard output stream.
*/
void stdout_(pEnv env)
{
    Node node;

    node.u.fil = stdout;
    node.op = FILE_;
    env->stck = pvec_add(env->stck, node);
}
#endif
