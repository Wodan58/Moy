/*
    module  : stderr.c
    version : 1.10
    date    : 09/17/24
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
    vec_push(env->stck, node);
}
#endif
