/*
    module  : conts.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef CONTS_C
#define CONTS_C

/**
Q0  OK  1080  conts  :  A  ->  [[P] [Q] ..]
Pushes current continuations. Buggy, do not use.
*/
void conts_(pEnv env)
{
    Node node;

    vec_copy_count(node.u.lis, env->prog, vec_size(env->prog));
    node.op = LIST_;
    vec_push(env->stck, node);
}
#endif
