/*
    module  : stderr.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef STDERR_C
#define STDERR_C

/**
OK 1190  stderr  :  A	->  S
Pushes the standard error stream.
*/
void stderr_(pEnv env)
{
    Node node;

    node.u.fil = stderr;
    node.op = FILE_;
    env->stck = pvec_add(env->stck, node);
}
#endif
