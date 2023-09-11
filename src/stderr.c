/*
    module  : stderr.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef STDERR_C
#define STDERR_C

/**
OK 1190  stderr  :  A	->  S
Pushes the standard error stream.
*/
void stderr_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.fil = stderr;
    node.op = FILE_;
    lst_push(env->stck, node);
#endif
}
#endif
