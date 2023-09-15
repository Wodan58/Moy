/*
    module  : popd.c
    version : 1.5
    date    : 09/15/23
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
    node = lst_pop(env->stck);
    (void)lst_pop(env->stck);
    lst_push(env->stck, node);
}
#endif
