/*
    module  : stdin.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef STDIN_C
#define STDIN_C

/**
OK 1170  stdin  :  A	->  S
Pushes the standard input stream.
*/
void stdin_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.fil = stdin;
    node.op = FILE_;
    lst_push(env->stck, node);
#endif
}
#endif
