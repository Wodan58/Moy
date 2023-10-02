/*
    module  : stdout.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef STDOUT_C
#define STDOUT_C

/**
OK 1180  stdout  :  A	->  S
Pushes the standard output stream.
*/
void stdout_(pEnv env)
{
    Node node;

    node.u.fil = stdout;
    node.op = FILE_;
    env->stck = pvec_add(env->stck, node);
}
#endif
