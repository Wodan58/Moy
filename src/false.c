/*
    module  : false.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef FALSE_C
#define FALSE_C

/**
IMMEDIATE 1000  false  :  A	->  false
Pushes the value false.
*/
void false_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.num = 0;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
#endif
}
#endif
