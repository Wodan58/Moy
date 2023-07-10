/*
    module  : stdin.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef STDIN_C
#define STDIN_C

/**
OK 1170  stdin  :  A	->  S
Pushes the standard input stream.
*/
void stdin_(pEnv env)
{
    Node node;

    node.u.fil = stdin;
    node.op = FILE_;
    vec_push(env->stck, node);
}
#endif
