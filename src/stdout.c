/*
    module  : stdout.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef STDOUT_C
#define STDOUT_C

/**
Q0  IMMEDIATE  1180  stdout  :  A  ->  S
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
