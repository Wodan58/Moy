/*
    module  : stdin.c
    version : 1.9
    date    : 03/05/24
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
    env->stck = pvec_add(env->stck, node);
}
#endif
