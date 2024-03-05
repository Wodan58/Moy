/*
    module  : stderr.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef STDERR_C
#define STDERR_C

/**
Q0  IMMEDIATE  1190  stderr  :  A  ->  S
[FOREIGN] Pushes the standard error stream.
*/
void stderr_(pEnv env)
{
    Node node;

    node.u.fil = stderr;
    node.op = FILE_;
    env->stck = pvec_add(env->stck, node);
}
#endif
