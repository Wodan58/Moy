/*
    module  : less.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef LESS_C
#define LESS_C

/**
OK 2260  <\0less  :  DDA	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X less than Y.  Also supports float.
*/
void less_(pEnv env)
{
    Node first, second, node;

    PARM(2, ANYTYPE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    if (first.op == SET_ || second.op == SET_)
        node.u.num = first.u.set != second.u.set &&
                     !(first.u.set & ~second.u.set);
    else
        node.u.num = Compare(env, first, second) < 0;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
