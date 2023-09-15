/*
    module  : conts.c
    version : 1.5
    date    : 09/15/23
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

    lst_init(node.u.lis);
    lst_copy(node.u.lis, env->prog);
    node.op = LIST_;
    lst_push(env->stck, node);
}
#endif
