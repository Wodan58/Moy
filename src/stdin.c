/*
    module  : stdin.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef STDIN_C
#define STDIN_C

/**
Q0  IMMEDIATE  1170  stdin  :  A  ->  S
[FOREIGN] Pushes the standard input stream.
*/
void stdin_(pEnv env)
{
    Node node;

    node.u.fil = stdin;
    node.op = FILE_;
    vec_push(env->stck, node);
}
#endif
