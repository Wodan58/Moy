/*
    module  : stdout.c
    version : 1.1
    date    : 07/10/23
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
    vec_push(env->stck, node);
}
#endif
