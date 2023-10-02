/*
    module  : popd.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef POPD_C
#define POPD_C

/**
OK 1260  popd  :  DDA	Y Z  ->  Z
As if defined by:   popd  ==  [pop] dip
*/
void popd_(pEnv env)
{
    Node node;

    PARM(2, ANYTYPE);
    env->stck = pvec_pop(env->stck, &node);
    env->stck = pvec_del(env->stck);
    env->stck = pvec_add(env->stck, node);
}
#endif
