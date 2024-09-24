/*
    module  : stdout.c
    version : 1.10
    date    : 09/17/24
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
    vec_push(env->stck, node);
}
#endif
