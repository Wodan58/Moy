/*
    module  : stdout.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef STDOUT_C
#define STDOUT_C

/**
OK 1180  stdout  :  A	->  S
Pushes the standard output stream.
*/
void stdout_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.fil = stdout;
    node.op = FILE_;
    lst_push(env->stck, node);
#endif
}
#endif
