/*
    module  : conts.c
    version : 1.6
    date    : 10/02/23
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

    node.u.lis = pvec_init();
    pvec_copy(node.u.lis, env->prog);
    node.op = LIST_;
    env->stck = pvec_add(env->stck, node);
}
#endif
