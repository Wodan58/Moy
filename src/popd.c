/*
    module  : popd.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef POPD_C
#define POPD_C

/**
Q0  OK  1260  popd  :  DDA  Y Z  ->  Z
As if defined by:   popd  ==  [pop] dip
*/
void popd_(pEnv env)
{
    Node node;

    PARM(2, ANYTYPE);
    node = vec_pop(env->stck);
    (void)vec_pop(env->stck);
    vec_push(env->stck, node);
}
#endif
