/*
    module  : stderr.c
    version : 1.2
    date    : 08/23/23
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
    lst_push(env->stck, node);
}
#endif
