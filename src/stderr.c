/*
    module  : stderr.c
    version : 1.1
    date    : 07/10/23
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
    vec_push(env->stck, node);
}
#endif
