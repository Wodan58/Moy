/*
    module  : conts.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef CONTS_C
#define CONTS_C

/**
OK 1080  conts  :  ->  A	[[P] [Q] ..]
Pushes current continuations. Buggy, do not use.
*/
void conts_(pEnv env)
{
    Node node;

    vec_init(node.u.lis);
    vec_copy(node.u.lis, env->prog);
    node.op = LIST_;
    vec_push(env->stck, node);
}
#endif
