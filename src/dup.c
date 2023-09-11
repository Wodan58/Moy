/*
    module  : dup.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef DUP_C
#define DUP_C

/**
OK 1210  dup  :  A 	X  ->  X X
Pushes an extra copy of X onto stack.
*/
void dup_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, ANYTYPE);
    node = lst_back(env->stck);
    lst_push(env->stck, node);
#endif
}
#endif
